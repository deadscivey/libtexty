#pragma once
#include "html/Node.h"
#include "html/goose/BoostChecker.h"
#include "html/goose/TextCleaner.h"
#include "html/goose/TextNodeCollector.h"
#include "html/goose/GooseOptions.h"
#include "html/goose/NodeScorer.h"
#include "html/goose/util.h"
#include "stemming/Utf8Stemmer.h"
#include <glog/logging.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace texty { namespace html { namespace goose {

using stemming::Utf8Stemmer;

template<typename TNodeScorer, typename TTextCleaner,
  typename TTextCollector, typename TStopwordCounter,
  typename TBoostChecker>
class BaseContentExtractor {
 public:
  std::string extract(const GooseOptions &opts,
      TStopwordCounter &stopwords, const Node &rootNode) {

    TBoostChecker boostChecker(opts, stopwords);
    TTextCollector collector(stopwords);
    TNodeScorer scorer(stopwords, collector, boostChecker, rootNode);
    TTextCleaner cleaner;
    LOG(INFO) << "extracting";
    LOG(INFO) << "scorer.process() start";
    scorer.process();
    LOG(INFO) << "scorer.process() end";
    auto topNode = scorer.getTopNode();
    LOG(INFO) << "topNode isGood? " << topNode.good();
    int topNodeScore = scorer.getTopNodeScore();
    LOG(INFO) << topNode.getText();
    std::ostringstream contentOss;
    double thresholdScore = ((double) topNodeScore) * 0.08;
    size_t i = 0;
    for (auto node: topNode.children()) {
      LOG(INFO) << "child: " << i;
      i++;
      auto nodeText = cleaner.getText(node);
      if (node.isElement() && !node.hasTag(Tag::P)) {
        if (hasHighLinkDensity(node, nodeText)) {
          continue;
        }
        if (!node.hasTag(Tag::TD)) {
          auto nodeScore = (double) scorer.getNodeScore(node);
          if (nodeScore < thresholdScore) {
            continue;
          }
        }
      }
      if (stopwords.countStopwords(nodeText) < 3) {
        continue;
      }
      contentOss << nodeText;
    }
    LOG(INFO) << "extracted";
    return contentOss.str();
  }
};

}}} // texty::html::goose
