#pragma once
#include <unordered_map>
#include <map>
#include "NGram.h"
#include "Language.h"

namespace texty { namespace language_detection {

const std::unordered_map<NGram<uint32_t, 1>, std::unordered_map<Language, double>> & get_one_grams();
const std::unordered_map<NGram<uint32_t, 2>, std::unordered_map<Language, double>> & get_two_grams();
const std::unordered_map<NGram<uint32_t, 3>, std::unordered_map<Language, double>> & get_three_grams();

}} // texty::language_detection

