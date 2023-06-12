#include "parameters/baseparameter_nb.h"

#include "engine/api/base_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_BaseParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;

    nb::enum_<BaseParameters::SnappingType>(m, "SnappingType")
        .value("Default", BaseParameters::SnappingType::Default)
        .value("Any", BaseParameters::SnappingType::Any)
        .export_values();

    nb::enum_<BaseParameters::OutputFormatType>(m, "OutputFormatType")
        .value("JSON", BaseParameters::OutputFormatType::JSON)
        .value("FLATBUFFERS", BaseParameters::OutputFormatType::FLATBUFFERS)
        .export_values();

    nb::class_<BaseParameters>(m, "BaseParameters")
        .def(nb::init<
                std::vector<osrm::util::Coordinate>,
                std::vector<boost::optional<osrm::engine::Hint>>,
                std::vector<boost::optional<double>>,
                std::vector<boost::optional<osrm::engine::Bearing>>,
                std::vector<boost::optional<osrm::engine::Approach>>,
                bool,
                std::vector<std::string>,
                const BaseParameters::SnappingType
            >(),
                "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                "radiuses"_a = std::vector<boost::optional<double>>(),
                "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                "approaches"_a = std::vector<boost::optional<osrm::engine::Approach>>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = BaseParameters::SnappingType::Default
            )
        .def_rw("coordinates", &BaseParameters::coordinates)
        .def_rw("hints", &BaseParameters::hints)
        .def_rw("radiuses", &BaseParameters::radiuses)
        .def_rw("bearings", &BaseParameters::bearings)
        .def_rw("approaches", &BaseParameters::approaches)
        .def_rw("exclude", &BaseParameters::exclude)
        .def_rw("format", &BaseParameters::format)
        .def_rw("generate_hints", &BaseParameters::generate_hints)
        .def_rw("skip_waypoints", &BaseParameters::skip_waypoints)
        .def_rw("snapping", &BaseParameters::snapping)
        .def("IsValid", &BaseParameters::IsValid);
}
