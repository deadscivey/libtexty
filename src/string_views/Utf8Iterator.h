#pragma once

#include <string>
#include "string_views/BaseUtf8Iterator.h"

namespace texty { namespace string_views {

class Utf8Iterator : public BaseUtf8Iterator<Utf8Iterator,
    std::pair<size_t, uint32_t>>  {
 protected:
  using deref_result = std::pair<size_t, uint32_t>;
 public:
  using parent_type = BaseUtf8Iterator<Utf8Iterator, deref_result>;
  deref_result dereference() const;
  template<typename ...Args>
  Utf8Iterator(Args... args)
    : parent_type(std::forward<Args>(args)...) {}  
};

}} // texty::string_views

