#pragma once
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <glog/logging.h>
#include "search/RabinFingerprinter.h"
#include "search/RollingRabinHash.h"

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
    std::set<size_t> termsLengths;
    for (auto &elem: terms_) {
      termsLengths.insert(elem.first);
    }
    RollingRabinHash<TCollection, 64> roller(
      alpha_, 5120000, coll, termsLengths
    );
    result_list results;
    while (roller.good()) {
      for (auto &hashed: roller.getHashes()) {
        LOG(INFO) << "\t[ " << hashed.first << " ]\t:\t" << hashed.second;
        auto &sameSize = terms_.at(hashed.first);
        if (sameSize.count(hashed.second) > 0) {
          auto &matched = sameSize.at(hashed.second);
          results.push_back(std::make_pair(
            matched, std::make_pair(
              roller.currentOffset() - hashed.first,
              roller.currentOffset()
            )
          ));
        }
      }
      if (!roller.step()) {
        break;
      }
    }
    return results;
  }
};

}} // texty::search
