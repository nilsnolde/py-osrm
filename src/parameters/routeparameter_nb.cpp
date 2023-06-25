#include "parameters/baseparameter_nb.h"

#include "engine/api/route_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_RouteParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::RouteParameters;

    nb::enum_<RouteParameters::GeometriesType>(m, "GeometriesType")
        .value("Polyline", RouteParameters::GeometriesType::Polyline)
        .value("Polyline6", RouteParameters::GeometriesType::Polyline6)
        .value("GeoJSON", RouteParameters::GeometriesType::GeoJSON)
        .export_values();

    nb::enum_<RouteParameters::OverviewType>(m, "OverviewType")
        .value("Simplified", RouteParameters::OverviewType::Simplified)
        .value("Full", RouteParameters::OverviewType::Full)
        .value("False", RouteParameters::OverviewType::False)
        .export_values();

    nb::enum_<RouteParameters::AnnotationsType>(m, "AnnotationsType", nb::is_arithmetic())
        .value("None_", RouteParameters::AnnotationsType::None)
        .value("Duration", RouteParameters::AnnotationsType::Duration)
        .value("Nodes", RouteParameters::AnnotationsType::Nodes)
        .value("Distance", RouteParameters::AnnotationsType::Distance)
        .value("Weight", RouteParameters::AnnotationsType::Weight)
        .value("Datasources", RouteParameters::AnnotationsType::Datasources)
        .value("Speed", RouteParameters::AnnotationsType::Speed)
        .value("All", RouteParameters::AnnotationsType::All)
        .export_values();

    nb::class_<RouteParameters, BaseParameters>(m, "RouteParameters")
        .def(nb::init<>())
        .def(nb::init<
                const bool,
                const bool,
                const RouteParameters::AnnotationsType,
                const RouteParameters::GeometriesType,
                const RouteParameters::OverviewType,
                const boost::optional<bool>,
                std::vector<std::size_t>,
                    std::vector<osrm::util::Coordinate>,
                    std::vector<boost::optional<osrm::engine::Hint>>,
                    std::vector<boost::optional<double>>,
                    std::vector<boost::optional<osrm::engine::Bearing>>,
                    std::vector<boost::optional<osrm::engine::Approach>>,
                    bool,
                    std::vector<std::string>,
                    const BaseParameters::SnappingType
            >(),
                "steps"_a,
                "alternatives"_a,
                "annotations"_a = RouteParameters::AnnotationsType::None,
                "geometries"_a,
                "overview"_a,
                "continue_straight"_a,
                "waypoints"_a = std::vector<std::size_t>(),
                    "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                    "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                    "radiuses"_a = std::vector<boost::optional<double>>(),
                    "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                    "approaches"_a = std::vector<boost::optional<osrm::engine::Approach>>(),
                    "generate_hints"_a = true,
                    "exclude"_a = std::vector<std::string>(),
                    "snapping"_a = BaseParameters::SnappingType::Default
            )
        .def_rw("steps", &RouteParameters::steps)
        .def_rw("alternatives", &RouteParameters::alternatives)
        .def_rw("number_of_alternatives", &RouteParameters::number_of_alternatives)
        .def_rw("annotations", &RouteParameters::annotations)
        .def_rw("annotations_type", &RouteParameters::annotations_type)
        .def_rw("geometries", &RouteParameters::geometries)
        .def_rw("overview", &RouteParameters::overview)
        .def_rw("continue_straight", &RouteParameters::continue_straight)
        .def("IsValid", &RouteParameters::IsValid)
        .def("__and__", [](RouteParameters::AnnotationsType lhs, RouteParameters::AnnotationsType rhs) {
            return static_cast<bool>(
                static_cast<std::underlying_type_t<RouteParameters::AnnotationsType>>(lhs) &
                static_cast<std::underlying_type_t<RouteParameters::AnnotationsType>>(rhs));
        }, nb::is_operator())
        .def("__or__", [](RouteParameters::AnnotationsType lhs, RouteParameters::AnnotationsType rhs) {
            return RouteParameters::AnnotationsType(
                static_cast<std::underlying_type_t<RouteParameters::AnnotationsType>>(lhs) |
                static_cast<std::underlying_type_t<RouteParameters::AnnotationsType>>(rhs));
        }, nb::is_operator())
        .def("__ior__", [](RouteParameters::AnnotationsType lhs, RouteParameters::AnnotationsType rhs) {
            return lhs = lhs | rhs;
        }, nb::is_operator());
}
