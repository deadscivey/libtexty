#include <unordered_map>
#include <map>
#include <string>

#include <folly/DynamicConverter.h>
#include <folly/FileUtil.h>
#include <folly/dynamic.h>
#include <folly/json.h>

#include "language_detection/LanguageProfile.h"
#include "NGram.h"
#include "Language.h"

using namespace std;

namespace texty { namespace language_detection {

LanguageProfile::LanguageProfile(one_gram_map ones,
    two_gram_map twos, three_gram_map threes)
  : oneGrams_(std::move(ones)),
    twoGrams_(std::move(twos)),
    threeGrams_(std::move(threes)) {}

LanguageProfile::LanguageProfile(){}

LanguageProfile::LanguageProfile(LanguageProfile &&other) {
  oneGrams_ = std::move(other.oneGrams_);
  twoGrams_ = std::move(other.twoGrams_);
  threeGrams_ = std::move(other.threeGrams_);
}

LanguageProfile::LanguageProfile(const LanguageProfile &other) {
  oneGrams_ = other.oneGrams_;
  twoGrams_ = other.twoGrams_;
  threeGrams_ = other.threeGrams_;
}

LanguageProfile& LanguageProfile::operator=(LanguageProfile &&other) {
  oneGrams_ = std::move(other.oneGrams_);
  twoGrams_ = std::move(other.twoGrams_);
  threeGrams_ = std::move(other.threeGrams_);
  return *this;
}

LanguageProfile& LanguageProfile::operator=(const LanguageProfile &other) {
  oneGrams_ = other.oneGrams_;
  twoGrams_ = other.twoGrams_;
  threeGrams_ = other.threeGrams_;
  return *this;
}

const LanguageProfile::lang_map& LanguageProfile::getScores(NGram<uint32_t, 1> ngram) {
  auto found = oneGrams_.find(ngram);
  if (found == oneGrams_.end()) {
    return emptyScores_;
  }
  return found->second;
}

const LanguageProfile::lang_map& LanguageProfile::getScores(NGram<uint32_t, 2> ngram) {
  auto found = twoGrams_.find(ngram);
  if (found == twoGrams_.end()) {
    return emptyScores_;
  }
  return found->second;
}

const LanguageProfile::lang_map& LanguageProfile::getScores(NGram<uint32_t, 3> ngram) {
  auto found = threeGrams_.find(ngram);
  if (found == threeGrams_.end()) {
    return emptyScores_;    
  }
  return found->second;
}

LanguageProfile LanguageProfile::loadFromJsonString(const std::string& jsonData) {
  LanguageProfile result;
  auto data = folly::parseJson(jsonData);
  auto ones = data[0];
  for (auto gramPair: ones) {
    NGram<uint32_t, 1> key {folly::convertTo<uint32_t>(gramPair[0][0])};
    std::unordered_map<Language, double> langScores;
    for (auto langPair: gramPair[1]) {
      auto lang = languageFromCode(folly::convertTo<string>(langPair[0]));
      auto score = folly::convertTo<double>(langPair[1]);
      langScores.insert(std::make_pair(lang, score));
    }
    result.oneGrams_.insert(std::make_pair(
      key, langScores
    ));
  }
  for (auto gramPair: data[1]) {
    NGram<uint32_t, 2> key {
      folly::convertTo<uint32_t>(gramPair[0][0]),
      folly::convertTo<uint32_t>(gramPair[0][1])
    };
    std::unordered_map<Language, double> langScores;
    for (auto langPair: gramPair[1]) {
      auto lang = languageFromCode(folly::convertTo<string>(langPair[0]));
      auto score = folly::convertTo<double>(langPair[1]);
      langScores.insert(std::make_pair(lang, score));
    }
    result.twoGrams_.insert(std::make_pair(
      key, langScores
    ));
  }
  for (auto gramPair: data[2]) {
    NGram<uint32_t, 3> key {
      folly::convertTo<uint32_t>(gramPair[0][0]),
      folly::convertTo<uint32_t>(gramPair[0][1]),
      folly::convertTo<uint32_t>(gramPair[0][2])
    };
    std::unordered_map<Language, double> langScores;
    for (auto langPair: gramPair[1]) {
      auto lang = languageFromCode(folly::convertTo<string>(langPair[0]));
      auto score = folly::convertTo<double>(langPair[1]);
      langScores.insert(std::make_pair(lang, score));
    }
    result.threeGrams_.insert(std::make_pair(
      key, langScores
    ));
  }
  return result;
  // array of gram data

}
LanguageProfile LanguageProfile::loadFromFile(const std::string& fpath) {
  string data;
  folly::readFile(fpath.c_str(), data);
  return LanguageProfile::loadFromJsonString(data);
}


}} // texty::language_detection
