#include "parameters/nearestparameter_nb.h"

#include "engine/api/nearest_parameters.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_NearestParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::NearestParameters;

    nb::class_<NearestParameters, BaseParameters>(m, "NearestParameters")
        .def(nb::init<>())
        .def_rw("number_of_results", &NearestParameters::number_of_results)
        .def("IsValid", &NearestParameters::IsValid);
}
