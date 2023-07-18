#include "parameters/matchparameter_nb.h"

#include "engine/api/match_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_MatchParameters(nb::module_& m) {
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::MatchParameters;

    nb::class_<MatchParameters, RouteParameters>(m, "MatchParameters")
        .def(nb::init<>())
        .def("__init__", [](MatchParameters* t,
                std::vector<unsigned> timestamps,
                MatchParameters::GapsType gaps_type,
                bool tidy,
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
                new (t) MatchParameters();

                t->timestamps = std::move(timestamps);
                t->gaps = gaps_type;
                t->tidy = tidy;

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
                "timestamps"_a = std::vector<unsigned>(),
                "gaps"_a = std::string(),
                "tidy"_a = false,
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
        .def_rw("timestamps", &MatchParameters::timestamps)
        .def_rw("gaps", &MatchParameters::gaps)
        .def_rw("tidy", &MatchParameters::tidy)
        .def("IsValid", &MatchParameters::IsValid);

    nb::class_<MatchParameters::GapsType>(m, "MatchGapsType")
        .def("__init__", [](MatchParameters::GapsType* t, const std::string& str) {
            MatchParameters::GapsType gaps = osrm_nb_util::str_to_enum(str, "MatchGapsType", gaps_map);
            new (t) MatchParameters::GapsType(gaps);
        })
        .def("__repr__", [](MatchParameters::GapsType type) {
            return osrm_nb_util::enum_to_str(type, "MatchGapsType", gaps_map);
        });
    nb::implicitly_convertible<std::string, MatchParameters::GapsType>();
}
