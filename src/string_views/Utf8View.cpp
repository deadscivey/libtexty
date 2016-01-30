#include "string_views/Utf8View.h"
#include "string_views/Utf8Iterator.h"
#include <string>

using namespace std;

namespace texty { namespace string_views {

Utf8View::Utf8View(const string &text)
  : textStart_(text.c_str()),
    textEnd_(text.c_str() + text.size()) {}

Utf8View::Utf8View(const char *start, size_t len)
  : textStart_(start),
    textEnd_(start + len){}

Utf8View::Utf8View(const char *start, const char *endPtr)
  : textStart_(start),
    textEnd_(endPtr){}

size_t Utf8View::bytes() {
  uintptr_t startPtr = (uintptr_t) textStart_;
  uintptr_t endPtr = (uintptr_t) textEnd_;
  return endPtr - startPtr;
}

Utf8Iterator Utf8View::begin() {
  return Utf8Iterator(textStart_, textEnd_);
}

Utf8Iterator Utf8View::end() {
  return Utf8Iterator(textEnd_, textEnd_);
}

}} // texty::string_views
