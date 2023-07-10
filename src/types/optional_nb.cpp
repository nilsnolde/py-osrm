#include "types/optional_nb.h"

#include "engine/api/base_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/pair.h>

namespace nb = nanobind;

void init_Optional(nb::module_& m) {
    using OptionalBool = boost::optional<bool>;
    nb::class_<OptionalBool>(m, "OptionalBool")
        .def(nb::init<>())
        .def(nb::init<bool>())
        .def(nb::init_implicit<bool>());

    using OptionalDouble = boost::optional<double>;
    nb::class_<OptionalDouble>(m, "OptionalDouble")
        .def(nb::init<>())
        .def(nb::init<double>())
        .def(nb::init_implicit<double>());

    using OptionalApproach = boost::optional<osrm::engine::Approach>;
    nb::class_<OptionalApproach>(m, "OptionalApproach")
        .def(nb::init<>())
        .def(nb::init<osrm::engine::Approach>())
        .def(nb::init_implicit<osrm::engine::Approach>());

    using OptionalBearing = boost::optional<osrm::engine::Bearing>;
    nb::class_<OptionalBearing>(m, "OptionalBearing")
        .def(nb::init<>())
        .def(nb::init<osrm::engine::Bearing>())
        .def(nb::init_implicit<osrm::engine::Bearing>())
        .def("__init__", [](OptionalBearing* t, std::pair<int16_t, int16_t> pair) {
            new (t) OptionalBearing({pair.first, pair.second});
         });
    nb::implicitly_convertible<std::pair<int16_t, int16_t>, OptionalBearing>();
}
