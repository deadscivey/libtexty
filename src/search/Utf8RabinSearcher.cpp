#include "search/Utf8RabinSearcher.h"

namespace texty { namespace search {

Utf8RabinSearcher::Utf8RabinSearcher(uint32_t alpha,
    Utf8RabinSearcher::term_map terms)
  : alpha_(alpha), terms_(std::move(terms)) {}


uint32_t Utf8RabinSearcher::alpha() const {
  return alpha_;
}

size_t Utf8RabinSearcher::maxTermSize() const {
  if (terms_.empty()) {
    return 0;
  }
  return terms_.rbegin()->first;
}

size_t Utf8RabinSearcher::minTermsize() const {
  if (terms_.empty()) {
    return 0;
  }
  return terms_.begin()->first;
}

}} // texty::search
