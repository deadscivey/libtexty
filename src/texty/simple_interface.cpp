#include "texty/simple_interface.h"
#include "texty/ConstantSpaceSimHasher.h"
#include "hashing.h"

using namespace std;
namespace texty { namespace simple_interface {

uint64_t simhashText(const std::string &text, uint64_t seed) {
  ConstantSpaceSimHasher<1024, 10> hasher([](const std::string &arg, uint64_t sd) {
    return hashing::city_hash_64(arg, sd);
  }, seed);
  return hasher.hash(text);
}

}} // texty::simple_interface

