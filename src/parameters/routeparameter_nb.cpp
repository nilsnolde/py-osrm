#include "parameters/routeparameter_nb.h"

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

    nb::class_<RouteParameters, BaseParameters>(m, "RouteParameters")
        .def(nb::init<>())
        .def("__init__", [](RouteParameters* t,
                const bool steps,
                int number_of_alternatives,
                const std::vector<RouteParameters::AnnotationsType>& annotations,
                RouteParameters::GeometriesType geometries,
                RouteParameters::OverviewType overview,
                const boost::optional<bool> continue_straight,
                std::vector<std::size_t> waypoints,
                    std::vector<osrm::util::Coordinate> coordinates,
                    std::vector<boost::optional<osrm::engine::Hint>> hints,
                    std::vector<boost::optional<double>> radiuses,
                    std::vector<boost::optional<osrm::engine::Bearing>> bearings,
                    const std::vector<boost::optional<osrm::engine::Approach>>& approaches,
                    bool generate_hints,
                    std::vector<std::string> exclude,
                    const BaseParameters::SnappingType snapping
            ) {
                new (t) RouteParameters();

                osrm_nb_util::assign_routeparameters(t,
                                                     steps,
                                                     number_of_alternatives,
                                                     annotations,
                                                     geometries,
                                                     overview,
                                                     continue_straight,
                                                     waypoints);

                osrm_nb_util::assign_baseparameters(t,
                                                    coordinates,
                                                    hints,
                                                    radiuses,
                                                    bearings,
                                                    approaches,
                                                    generate_hints,
                                                    exclude,
                                                    snapping);
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

    nb::class_<RouteParameters::GeometriesType>(m, "RouteGeometriesType")
        .def("__init__", [](RouteParameters::GeometriesType* t, const std::string& str) {
            RouteParameters::GeometriesType geometries = osrm_nb_util::str_to_enum(str, "RouteGeometriesType", geometries_map);
            new (t) RouteParameters::GeometriesType(geometries);
        })
        .def("__repr__", [](RouteParameters::GeometriesType type) {
            return osrm_nb_util::enum_to_str(type, "RouteGeometriesType", geometries_map);
        });
    nb::implicitly_convertible<std::string, RouteParameters::GeometriesType>();

    nb::class_<RouteParameters::OverviewType>(m, "RouteOverviewType")
        .def("__init__", [](RouteParameters::OverviewType* t, const std::string& str) {
            RouteParameters::OverviewType overview = osrm_nb_util::str_to_enum(str, "RouteOverviewType", overview_map);
            new (t) RouteParameters::OverviewType(overview);
        })
        .def("__repr__", [](RouteParameters::OverviewType type) {
            return osrm_nb_util::enum_to_str(type, "RouteOverviewType", overview_map);
        });
    nb::implicitly_convertible<std::string, RouteParameters::OverviewType>();

    nb::class_<RouteParameters::AnnotationsType>(m, "RouteAnnotationsType")
        .def("__init__", [](RouteParameters::AnnotationsType* t, const std::string& str) {
            RouteParameters::AnnotationsType annotation = osrm_nb_util::str_to_enum(str, "RouteAnnotationsType", route_annotations_map);
            new (t) RouteParameters::AnnotationsType(annotation);
        })
        .def("__repr__", [](RouteParameters::AnnotationsType type) {
            return std::to_string((int)type);
        })
        .def("__and__", [](RouteParameters::AnnotationsType lhs, RouteParameters::AnnotationsType rhs) {
            return lhs & rhs;
        }, nb::is_operator())
        .def("__or__", [](RouteParameters::AnnotationsType lhs, RouteParameters::AnnotationsType rhs) {
            return lhs | rhs;
        }, nb::is_operator())
        .def("__ior__", [](RouteParameters::AnnotationsType& lhs, RouteParameters::AnnotationsType rhs) {
            return lhs = lhs | rhs;
        }, nb::is_operator());
    nb::implicitly_convertible<std::string, RouteParameters::AnnotationsType>();
}
