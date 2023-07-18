#include "parameters/baseparameter_nb.h"

#include "engine/api/base_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_BaseParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;

    nb::class_<BaseParameters>(m, "BaseParameters")
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

    nb::class_<BaseParameters::SnappingType>(m, "SnappingType")
        .def("__init__", [](BaseParameters::SnappingType* t, const std::string& str) {
            BaseParameters::SnappingType snapping = osrm_nb_util::str_to_enum(str, "SnappingType", snapping_map);
            new (t) BaseParameters::SnappingType(snapping);
        })
        .def("__repr__", [](BaseParameters::SnappingType type) {
            return osrm_nb_util::enum_to_str(type, "SnappingType", snapping_map);
        });
    nb::implicitly_convertible<std::string, BaseParameters::SnappingType>();

    nb::class_<BaseParameters::OutputFormatType>(m, "OutputFormatType")
        .def("__init__", [](BaseParameters::OutputFormatType* t, const std::string& str) {
            BaseParameters::OutputFormatType output = osrm_nb_util::str_to_enum(str, "OutputFormatType", output_map);
            new (t) BaseParameters::OutputFormatType(output);
        })
        .def("__repr__", [](BaseParameters::OutputFormatType type) {
            return osrm_nb_util::enum_to_str(type, "OutputFormatType", output_map);
        });
    nb::implicitly_convertible<std::string, BaseParameters::OutputFormatType>();
}
