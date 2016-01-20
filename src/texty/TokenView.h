#pragma once
#include "texty/Utf8View.h"
#include <string>

namespace texty {

class TokenView {
  const std::string &text_;
  Utf8View utf8View_;
 public:
  TokenView(const std::string &text);
  class Iterator {
   protected:
    Utf8View::Iterator start_;
    Utf8View::Iterator end_;
   public:
    Iterator(Utf8View::Iterator start, Utf8View::Iterator end);
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;
    bool good();
    operator bool();
    std::pair<size_t, size_t> operator*();
    Iterator& operator++();
    Iterator operator++(int);
  };
  Iterator begin();
  Iterator end();
};

} // texty
