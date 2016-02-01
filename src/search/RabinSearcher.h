#pragma once
#include <algorithm>
#include <string>
#include <type_traits>

namespace texty { namespace search {

template<typename TIter, typename TItem,
  typename TIgnore = typename std::enable_if<std::is_integral<TItem>::value>::type>
uint64_t rabinFingerprint(uint32_t alpha, size_t count,
    typename TIter start, typename TIter end) {
  if (count == 0) {
    return 0;
  }
  size_t expo = count - 1;
  uint64_t acc = 0;
  for (TIter it = start; it != end; it++) {
    TItem codePoint = *it;
    acc += std::pow(codePoint, expo);
    if (expo == 0) {
      break;
    }
    expo--;
  }
  return acc;
}

uint64_t rabinFingerprint(uint32_t, const std::string&, size_t, size_t);
uint64_t rabinFingerprint(uint32_t, const std::string&);
uint64_t rabinFingerprint(uint32_t, const char*, const char*);
uint64_t rabinFingerprint(uint32_t, const char*, size_t);


}} // texty::search