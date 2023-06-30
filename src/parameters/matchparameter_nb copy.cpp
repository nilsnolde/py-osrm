#include "parameters/matchparameter_nb.h"

#include "engine/api/match_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

//===============================
//this part requires some adjustment to the thing
//====================================

void init_MatchParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::MatchParameters;

    nb::enum_<MatchParameters::GapsType>(m, "GapsType")
        .value("Split", MatchParameters::GapsType::Split)
        .value("Ignore", MatchParameters::GapsType::Ignore)
        .export_values();

    nb::class_<MatchParameters, RouteParameters>(m, "MatchParameters")
        .def(nb::init<>())
        .def_rw("timestamps", &MatchParameters::timestamps)
        .def_rw("gaps", &MatchParameters::gaps)
        .def_rw("tidy", &MatchParameters::tidy)
        .def("IsValid", &MatchParameters::IsValid);
}
