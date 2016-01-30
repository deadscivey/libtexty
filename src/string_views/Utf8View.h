#pragma once

#include <string>
#include "string_views/Utf8Iterator.h"

namespace texty { namespace string_views {

class Utf8View {
  const char *textStart_ {nullptr};
  const char *textEnd_ {nullptr};
public:
  size_t bytes();
  Utf8View(const std::string &text);
  Utf8View(const char *text, size_t len);
  Utf8View(const char *textStart, const char *textEnd);
  Utf8Iterator begin();
  Utf8Iterator end();
};

}} // texty::string_views

