#include <pybind11/pybind11.h>
#include "hashing/ConstantSpaceSimHasher.h"
#include "hashing/hash_funcs.h"

using namespace std;

namespace texty { namespace python_interface {

uint64_t simhashText(const std::string &text, uint64_t seed) {
  hashing::ConstantSpaceSimHasher<1024, 10> hasher([](const std::string &arg, uint64_t sd) {
    return hashing::city_hash_64(arg, sd);
  }, seed);
  return hasher.hash(text);
}

}} // texty::python_interface



namespace py = pybind11;

PYBIND11_PLUGIN(textypy) {
    py::module m("textypy", "pybind11 example plugin");

    m.def("simhashText", &texty::python_interface::simhashText, "A function which adds two numbers");

    return m.ptr();
}
