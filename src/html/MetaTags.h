#pragma once
#include "html/HtmlDom.h"
#include "html/Node.h"
#include "html/Tag.h"

#include <map>
#include <string>

namespace texty { namespace html {

class MetaTags {
 protected:
  std::map<std::string, std::string> tagValues_;
 public:
  MetaTags(std::map<std::string, std::string> vals);
  static MetaTags extract(const Node& startingNode);
};


}} // text::html