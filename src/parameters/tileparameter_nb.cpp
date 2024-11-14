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

    // "Instantiates an instance of TileParameters.
    //         "Examples:
    //             >>> tile_params = osrm.TileParameters([17059, 11948, 15])
    //             >>> tile_params = osrm.TileParameters(
    //                     x = 17059,
    //                     y = 11948,
    //                     z = 15
    //                 )
    //             >>> tile_params.IsValid()
    //             True
    //         "Args:
    //             list (list of int): Instantiates an instance of TileParameters using an array [x, y, z].
    //             x (int): x value.
    //             y (int): y value.
    //             z (int): z value.
    //         "Returns:
    //             __init__ (osrm.TileParameters): A TileParameters object, for usage in Tile.
    //             IsValid (bool): A bool value denoting validity of parameter values.
    //         "Attributes:
    //             x (int): x value.
    //             y (int): y value.
    //             z (int): z value."

    nb::class_<TileParameters>(m, "TileParameters", nb::is_final())
        .def(nb::init<>())
        .def(nb::init<unsigned int, unsigned int, unsigned int>())
        .def("__init__", [](TileParameters* t, const std::vector<unsigned int>& coord) {
            if(coord.size() != 3) {
                throw std::runtime_error("Parameter must be an array [x, y, z]");
            }
            
            new (t) TileParameters{coord[0], coord[1], coord[2]};
         })
        .def_rw("x", &TileParameters::x)
        .def_rw("y", &TileParameters::y)
        .def_rw("z", &TileParameters::z)
        .def("IsValid", &TileParameters::IsValid);
    nb::implicitly_convertible<std::vector<unsigned int>, TileParameters>();
}
