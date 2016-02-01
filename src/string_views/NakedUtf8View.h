#pragma once

#include <string>
#include "string_views/NakedUtf8Iterator.h"
#include "string_views/BaseUtf8View.h"

namespace texty { namespace string_views {

class NakedUtf8View: public BaseUtf8View<NakedUtf8View, NakedUtf8Iterator> {
 public:
  using iterator = NakedUtf8Iterator;
  using parent_type = BaseUtf8View<NakedUtf8View, NakedUtf8Iterator>;
  template<typename ...Args>
  NakedUtf8View(Args... args)
    : parent_type(std::forward<Args>(args)...) {}  
};

}} // texty::string_views

