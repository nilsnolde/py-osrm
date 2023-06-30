#include "parameters/tileparameter_nb.h"

#include "engine/api/tile_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TileParameters(nb::module_& m) {
    using osrm::engine::api::TileParameters;

    nb::class_<TileParameters>(m, "TileParameters", nb::is_final())
        .def(nb::init<>())
        .def(nb::init<unsigned, unsigned, unsigned>(),
            "x"_a, "y"_a, "z"_a
        )
        .def("__init__", [](TileParameters* t, const std::vector<unsigned>& coord) {
            new (t) TileParameters{coord[0], coord[1], coord[2]};
         })
        .def_rw("x", &TileParameters::x)
        .def_rw("y", &TileParameters::y)
        .def_rw("z", &TileParameters::z)
        .def("IsValid", &TileParameters::IsValid);
    nb::implicitly_convertible<std::vector<unsigned>, TileParameters>();
}
