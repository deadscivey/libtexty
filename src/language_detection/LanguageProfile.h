#pragma once
#include <unordered_map>
#include <map>
#include <string>

#include "NGram.h"
#include "Language.h"

namespace texty { namespace language_detection {

class LanguageProfile {
 public:
  using lang_map = std::unordered_map<Language, double>;
  using one_gram_map = std::unordered_map<NGram<uint32_t, 1>, lang_map>;
  using two_gram_map = std::unordered_map<NGram<uint32_t, 2>, lang_map>;
  using three_gram_map = std::unordered_map<NGram<uint32_t, 3>, lang_map>;
 protected:
  one_gram_map oneGrams_;
  two_gram_map twoGrams_;
  three_gram_map threeGrams_;
  lang_map emptyScores_;
 public:
  LanguageProfile(one_gram_map, two_gram_map, three_gram_map);
  LanguageProfile();
  LanguageProfile(LanguageProfile &&other);
  LanguageProfile(const LanguageProfile &other);
  LanguageProfile& operator=(LanguageProfile &&other);
  LanguageProfile& operator=(const LanguageProfile &other);

  const lang_map& getScores(NGram<uint32_t, 1> ngram);
  const lang_map& getScores(NGram<uint32_t, 2> ngram);
  const lang_map& getScores(NGram<uint32_t, 3> ngram);

  static LanguageProfile loadFromJsonString(const std::string&);
  static LanguageProfile loadFromFile(const std::string&);
};

}} // texty::language_detection
