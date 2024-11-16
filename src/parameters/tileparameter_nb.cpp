#include "parameters/tileparameter_nb.h"

#include "engine/api/tile_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <stdexcept>

namespace nb = nanobind;
using namespace nb::literals;

void init_TileParameters(nb::module_& m) {
    using osrm::engine::api::TileParameters;

    nb::class_<TileParameters> tp(m, "TileParameters", nb::is_final());
        tp.doc() =  "TileParameters is an object containing configurations for OSRM tile requests.\n\n"
                    "Attributes:\n"
                    "   - x (int): x value.\n"
                    "   - y (int): y value.\n"
                    "   - z (int): z value.\n"
                    "Examples:\n"
                    "   >>> tile_params = osrm.TileParameters([17059, 11948, 15])\n"
                    "   >>> tile_params = osrm.TileParameters(\n"
                    "       x = 17059,\n"
                    "       y = 11948,\n"
                    "       z = 15\n"
                    "   )\n"
                    "   >>> tile_params.IsValid()\n"
                    "   True\n";
        tp.def(nb::init<>())
        .def(nb::init<unsigned int, unsigned int, unsigned int>(),
                "Instantiates an instance of TileParameters.\n"
                "Args:\n"
                "   - x (int): x value.\n"
                "   - y (int): y value.\n"
                "   - z (int): z value.\n"
                "Returns:\n"
                "    __init__ (osrm.TileParameters): A TileParameters object, for usage in Tile.\n"
        )
        .def("__init__", [](TileParameters* t, const std::vector<unsigned int>& coord) {
            if(coord.size() != 3) {
                throw std::runtime_error("Parameter must be an array [x, y, z]");
            }
            
            new (t) TileParameters{coord[0], coord[1], coord[2]};
         },
                "Instantiates an instance of TileParameters.\n"
                "Args:\n"
                "   - list (list of int): Instantiates an instance of TileParameters using an array [x, y, z].\n"
                "Returns:\n"
                "    __init__ (osrm.TileParameters): A TileParameters object, for usage in Tile.\n")
        .def_rw("x", &TileParameters::x)
        .def_rw("y", &TileParameters::y)
        .def_rw("z", &TileParameters::z)
        .def("IsValid", &TileParameters::IsValid);
    nb::implicitly_convertible<std::vector<unsigned int>, TileParameters>();
}
