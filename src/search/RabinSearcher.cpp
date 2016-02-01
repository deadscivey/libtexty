#include "search/RabinSearcher.h"
#include "util/macros.h"

using namespace std;

namespace texty { namespace search {

template<typename TIter>
uint64_t rabinFingerprint(uint32_t alpha, size_t count,
    typename TIter start, typename TIter end) {
  if (count == 0) {
    return 0;
  }
  size_t expo = count - 1;
  uint64_t acc = 0;
  for (TIter it = start; it != end; it++) {
    uint32_t codePoint = *it;
    acc += std::pow(codePoint, expo);
    if (expo == 0) {
      break;
    }
    expo--;
  }
  return acc;
}

uint64_t rabinFingerprint(uint32_t alpha, const string &text,
    size_t start, size_t end) {
  DEBUG_CHECK(start <= end);
  return rabinFingerprint(
      alpha, end - start,
      text.begin() + start, text.end() + end
  );
}

uint64_t rabinFingerprint(const std::string&);
uint64_t rabinFingerprint(const char*, const char*);
uint64_t rabinFingerprint(const char*, size_t);


}} // texty::search