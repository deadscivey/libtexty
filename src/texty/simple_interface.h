#pragma once
#include <string>
#include <cstdint>

namespace texty { namespace simple_interface {

uint64_t simhashText(const std::string &text, uint64_t seed);

}} // texty::simple_interface

