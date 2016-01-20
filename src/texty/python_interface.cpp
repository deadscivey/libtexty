#include <pybind11/pybind11.h>
#include "texty/simple_interface.h"

namespace py = pybind11;

PYBIND11_PLUGIN(textypy) {
    py::module m("textypy", "pybind11 example plugin");

    m.def("simhashText", &texty::simple_interface::simhashText, "A function which adds two numbers");

    return m.ptr();
}
