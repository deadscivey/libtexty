#include "html/HtmlDom.h"
#include "html/Node.h"
#include "html/Tag.h"
#include "html/MetaTags.h"

#include <map>
#include <string>
using namespace std;

namespace texty { namespace html {


MetaTags::MetaTags(std::map<std::string, std::string> vals)
  : tagValues_(std::move(vals)) {}

MetaTags MetaTags::extract(const Node &startingNode) {
  map<string, string> tags;
  string metaName;
  string metaVal;
  startingNode.dfs([&tags, &metaName, &metaVal](const Node &node) {
    if (!node.hasTag(Tag::META)) {
      return;
    }
    metaName = "";
    metaVal = "";
    if (node.getAttr("property", metaName)) {
      if (node.getAttr("content", metaVal)) {
        tags.insert(std::make_pair(metaName, metaVal));
      }
    } else if (node.getAttr("name", metaName)) {
      if (node.getAttr("content", metaVal)) {
        tags.insert(std::make_pair(metaName, metaVal));
      }
    } else if (node.getAttr("itemprop", metaName)) {
      if (metaName == "datePublished" && node.getAttr("datetime", metaVal)) {
        tags.insert(std::make_pair(metaName, metaVal));
      }
    }
  });
  return MetaTags(std::move(tags));
}

}} // text::html
