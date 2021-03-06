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
  const std::string& getFirstOrNothing(const std::vector<std::string>&) const;
 public:
  MetaTags(std::map<std::string, std::string> vals);
  static MetaTags extract(const Node& startingNode);
  const std::string& getPublishDate() const;
  const std::string& getTitle() const;
  bool has(const std::string&) const;
  const std::string& get(const std::string&) const;
  size_t size() const;
};


}} // text::html