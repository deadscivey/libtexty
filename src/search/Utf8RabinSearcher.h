#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <glog/logging.h>
#include "search/RabinFingerprinter.h"
#include "string_views/Utf8View.h"
#include "util/SmallVector.h"
#include "util/RollingQueue.h"

namespace texty { namespace search {

class Utf8RabinSearcher {
 protected:
  using hash_str_map = std::unordered_map<uint64_t, string_views::Utf8View>;
  using term_map = std::map<size_t, hash_str_map>;
  uint32_t alpha_ {0};
  term_map terms_;
  using codepoint_queue = util::RollingQueue<
    uint32_t, util::SmallVector<uint32_t, 64>
  >;
  size_t maxTermSize() const;
  size_t minTermsize() const;

 public:
  uint32_t alpha() const;
  using result_list = std::vector<std::pair<
    string_views::Utf8View, std::pair<size_t, size_t>
  >>;

  Utf8RabinSearcher(uint32_t alpha, term_map terms);

  template<typename TCollection>
  result_list findAll(const TCollection &coll) const {
    codepoint_queue cpQueue(maxTermSize(), 0);
    std::map<size_t, uint64_t> hashes;
    std::map<size_t, uint64_t> maxPows;
    for (auto &elem: terms_) {
      hashes.insert(std::make_pair(elem.first, 0));
      uint64_t maxPow = std::pow(alpha_, elem.first - 1);
      maxPows.insert(std::make_pair(elem.first, maxPow));
    }
    size_t currentIndex = 0;
    auto it = coll.begin();
    auto collEnd = coll.end();
    size_t maxTerm = maxTermSize();
    while (currentIndex < maxTerm && it != collEnd) {
      auto cp = (uint32_t) *it;
      cpQueue.push(cp);
      ++it;
      ++currentIndex;
    }
    if (it == collEnd) {
      return result_list();
    }
    for (auto &elem: hashes) {
      size_t n = elem.first - 1;
      std::ostringstream oss;
      for (size_t i = 0; i < elem.first; i++) {
        uint32_t current = cpQueue[i];
        oss << current << "  {" << n << "}  ";
        hashes[elem.first] += current * std::pow(alpha_, n);
        --n;
      }
      LOG(INFO) << "\t[ " << elem.first << " ]  :  " << oss.str();
    }
    result_list results;
    for (auto &elem: hashes) {
      auto &sameSize = terms_.at(elem.first);
      if (sameSize.count(elem.second) > 0) {
        auto &matched = sameSize.at(elem.second);
        results.push_back(std::make_pair(
          matched, std::make_pair(0, elem.first)
        ));
      }
    }
    for(; it != collEnd; ++it) {
      auto cp = (uint32_t) *it;
      for (auto &elem: hashes) {
        uint32_t front = cpQueue.at(0);
        LOG(INFO) << "front: " << front;
        hashes[elem.first] -= (front * maxPows[elem.first]);
        hashes[elem.first] *= alpha_;
        uint64_t val = hashes[elem.first];
        LOG(INFO) << " {" << elem.first << " } = " << val;
      }
      cpQueue.push(cp);
      ++currentIndex;
      for (auto &elem: hashes) {
        size_t idx = elem.first;
        LOG(INFO) << "idx: " << idx;
        auto newPoint = cpQueue.at(idx);
        hashes[elem.first] += newPoint;
        auto &sameSize = terms_.at(elem.first);
        if (sameSize.count(elem.second) > 0) {
          auto &matched = sameSize.at(elem.second);
          results.push_back(std::make_pair(
            matched, std::make_pair(currentIndex - elem.first, currentIndex)
          ));
        }
      }
    }
    return results;
  }
};

}} // texty::search
