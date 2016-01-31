#pragma once
#include <string>
#include "html/HtmlDom.h"
#include "html/goose/GooseOptions.h"
#include "Language.h"

namespace texty { namespace html { namespace goose {

class GooseContentExtractor {
  GooseOptions options_;
 public:
  GooseContentExtractor();
  GooseContentExtractor(GooseOptions);
  std::string extract(const HtmlDom &dom, Language);
  std::string extract(const std::string &htmlStr, Language);
};

}}} // texty::html::goose
