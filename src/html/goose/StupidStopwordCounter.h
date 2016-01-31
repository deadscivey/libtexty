#pragma once
#include "stopwords/StopwordFilter.h"
#include "Language.h"
#include <string>

namespace texty { namespace html { namespace goose {

class StupidStopwordCounter {
 protected:
  Language language_;
  stopwords::StopwordFilter stopwordFilter_;
 public:
  StupidStopwordCounter(Language lang);
  size_t countStopwords(const std::string&);
};

}}} // texty::html::goose
