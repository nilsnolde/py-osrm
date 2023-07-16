#include "parameters/baseparameter_nb.h"

#include "engine/api/route_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_RouteParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::RouteParameters;

    nb::enum_<RouteParameters::GeometriesType>(m, "RouteGeometriesType")
        .value("Polyline", RouteParameters::GeometriesType::Polyline)
        .value("Polyline6", RouteParameters::GeometriesType::Polyline6)
        .value("GeoJSON", RouteParameters::GeometriesType::GeoJSON)
        .export_values();

    nb::enum_<RouteParameters::OverviewType>(m, "RouteOverviewType")
        .value("Simplified", RouteParameters::OverviewType::Simplified)
        .value("Full", RouteParameters::OverviewType::Full)
        .value("False_", RouteParameters::OverviewType::False)
        .export_values();

    nb::enum_<RouteParameters::AnnotationsType>(m, "RouteAnnotationsType", nb::is_arithmetic())
        .value("None_", RouteParameters::AnnotationsType::None)
        .value("Duration", RouteParameters::AnnotationsType::Duration)
        .value("Nodes", RouteParameters::AnnotationsType::Nodes)
        .value("Distance", RouteParameters::AnnotationsType::Distance)
        .value("Weight", RouteParameters::AnnotationsType::Weight)
        .value("Datasources", RouteParameters::AnnotationsType::Datasources)
        .value("Speed", RouteParameters::AnnotationsType::Speed)
        .value("All", RouteParameters::AnnotationsType::All)
        .export_values()
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
        .def("__ior__", [](RouteParameters::AnnotationsType& lhs, RouteParameters::AnnotationsType rhs) {
            return lhs = lhs | rhs;
        }, nb::is_operator());

    nb::class_<RouteParameters, BaseParameters>(m, "RouteParameters")
        .def(nb::init<>())
        .def("__init__", [](RouteParameters* t,
                const bool steps,
                int number_of_alternatives,
                const std::vector<std::string>& annotations,
                const std::string& geometries,
                const std::string& overview,
                const boost::optional<bool> continue_straight,
                std::vector<std::size_t> waypoints,
                    std::vector<osrm::util::Coordinate> coordinates,
                    std::vector<boost::optional<osrm::engine::Hint>> hints,
                    std::vector<boost::optional<double>> radiuses,
                    std::vector<boost::optional<osrm::engine::Bearing>> bearings,
                    const std::vector<std::string*>& approaches,
                    bool generate_hints,
                    std::vector<std::string> exclude,
                    const std::string& snapping
            ) {
                new (t) RouteParameters();

                t->steps = steps;
                t->alternatives = (bool)number_of_alternatives;
                t->number_of_alternatives = number_of_alternatives;
                t->annotations = !annotations.empty();
                t->annotations_type = osrm_nb_util::get_routeannotations_type(annotations);         
                t->geometries = osrm_nb_util::get_geometries_type(geometries);
                t->overview = osrm_nb_util::get_overview_type(overview);
                t->continue_straight = continue_straight;
                t->waypoints = std::move(waypoints);
        
                t->coordinates = std::move(coordinates);
                t->hints = std::move(hints);
                t->radiuses = std::move(radiuses);
                t->bearings = std::move(bearings);
                t->approaches = std::move(osrm_nb_util::get_approach(approaches));
                t->generate_hints = generate_hints;
                t->exclude = std::move(exclude);
                t->snapping = osrm_nb_util::get_snapping_type(snapping);
            },
                "steps"_a = false,
                "alternatives"_a = 0,
                "annotations"_a = std::vector<std::string>(),
                "geometries"_a = std::string(),
                "overview"_a = std::string(),
                "continue_straight"_a = boost::optional<bool>(),
                "waypoints"_a = std::vector<std::size_t>(),
                    "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                    "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                    "radiuses"_a = std::vector<boost::optional<double>>(),
                    "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                    "approaches"_a = std::vector<std::string*>(),
                    "generate_hints"_a = true,
                    "exclude"_a = std::vector<std::string>(),
                    "snapping"_a = std::string()
            )
        .def_rw("steps", &RouteParameters::steps)
        .def_rw("alternatives", &RouteParameters::alternatives)
        .def_rw("number_of_alternatives", &RouteParameters::number_of_alternatives)
        .def_rw("annotations", &RouteParameters::annotations)
        .def_rw("annotations_type", &RouteParameters::annotations_type)
        .def_rw("geometries", &RouteParameters::geometries)
        .def_rw("overview", &RouteParameters::overview)
        .def_rw("continue_straight", &RouteParameters::continue_straight)
        .def("IsValid", &RouteParameters::IsValid);
}
