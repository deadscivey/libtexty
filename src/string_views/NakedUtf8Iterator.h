#pragma once

#include <string>
#include "string_views/BaseUtf8Iterator.h"

namespace texty { namespace string_views {

class NakedUtf8Iterator : public BaseUtf8Iterator<NakedUtf8Iterator, uint32_t> {
 public:
  using parent_type = BaseUtf8Iterator<NakedUtf8Iterator, uint32_t>;
  uint32_t dereference() const;

  template<typename ...Args>
  NakedUtf8Iterator(Args... args)
    : parent_type(std::forward<Args>(args)...) {}
};

}} // texty::string_views

