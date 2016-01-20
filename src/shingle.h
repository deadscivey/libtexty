#pragma once
#include <string>
#include <vector>

namespace shingle {
  std::vector<std::string> tokenize(const std::string &text);
  std::vector<std::string> shingle(const std::string &text, size_t n);

}