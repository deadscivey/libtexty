#include "html/goose/util.h"
#include "string_views/TokenView.h"
using namespace std;

namespace texty { namespace html { namespace goose {

using string_views::TokenView;

size_t getTokenCount(const string &text) {
  TokenView view(text);
  size_t tokenCount = 0;
  for (auto toke : view) {
    if (toke.second <= toke.first) {
      break;
    }
    tokenCount++;
  }
  return tokenCount;
}

bool hasHighLinkDensity(const Node &node, const string &nodeText) {
  size_t linkCount = 0;
  size_t linkTokenCount = 0;
  node.dfs([&linkCount, &linkTokenCount](const Node &elem) {
    if (!elem.hasTag(Tag::A)) {
      return;
    }
    linkCount++;
    linkTokenCount += getTokenCount(elem.getText());
  });
  if (linkCount == 0) {
    return false;
  }
  size_t nodeTokens = getTokenCount(nodeText);
  auto linkDivisor = ((double) linkTokenCount) / ((double) nodeTokens);
  auto score = linkDivisor * ((double) linkCount);
  return score > 1.0;
}

bool hasHighLinkDensity(const Node &node) {
  return hasHighLinkDensity(node, node.getText());
}

}}} // texty::html::goose
