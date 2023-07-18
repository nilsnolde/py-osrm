#include "parameters/tripparameter_nb.h"

#include "engine/api/trip_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TripParameters(nb::module_& m) {
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::TripParameters;

    nb::class_<TripParameters, RouteParameters>(m, "TripParameters")
        .def(nb::init<>())
        .def("__init__", [](TripParameters* t,
                TripParameters::SourceType source,
                TripParameters::DestinationType destination,
                bool,
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
                new (t) TripParameters();

                t->source = source;
                t->destination = destination;

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
                "source"_a = std::string(),
                "destination"_a = std::string(),
                "roundtrip"_a = true,
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
        .def_rw("source", &TripParameters::source)
        .def_rw("destination", &TripParameters::destination)
        .def_rw("roundtrip", &TripParameters::roundtrip)
        .def("IsValid", &TripParameters::IsValid);

    nb::class_<TripParameters::SourceType>(m, "TripSourceType")
        .def("__init__", [](TripParameters::SourceType* t, const std::string& str) {
            TripParameters::SourceType source = osrm_nb_util::str_to_enum(str, "TripSourceType", source_map);
            new (t) TripParameters::SourceType(source);
        })
        .def("__repr__", [](TripParameters::SourceType type) {
            return osrm_nb_util::enum_to_str(type, "TripSourceType", source_map);
        });
    nb::implicitly_convertible<std::string, TripParameters::SourceType>();

    nb::class_<TripParameters::DestinationType>(m, "TripDestinationType")
        .def("__init__", [](TripParameters::DestinationType* t, const std::string& str) {
            TripParameters::DestinationType dest = osrm_nb_util::str_to_enum(str, "TripDestinationType", dest_map);
            new (t) TripParameters::DestinationType(dest);
        })
        .def("__repr__", [](TripParameters::DestinationType type) {
            return osrm_nb_util::enum_to_str(type, "TripDestinationType", dest_map);
        });
    nb::implicitly_convertible<std::string, TripParameters::DestinationType>();
}
