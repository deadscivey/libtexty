#pragma once

#include <string>
#include "language_detection/LanguageProfiles.h"
#include "Language.h"

namespace texty { namespace language_detection {

class LanguageDetector {
 protected:
  LanguageProfiles profiles_;
 public:
  LanguageDetector(LanguageProfiles profiles);
  Language detect(const std::string&, size_t seed);
  std::map<Language, double> getProbabilities(const std::string&, size_t seed);
};

}} // texty::language_detection