#include "parameters/tripparameter_nb.h"

#include "engine/api/trip_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TripParameters(nb::module_& m) {
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::TripParameters;

    // "Instantiates an instance of TripParameters.
    //         "Examples:
    //             >>> trip_params = osrm.TripParameters(
    //                     coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],
    //                     source = 'any',
    //                     destination = 'last',
    //                     roundtrip = False
    //                 )
    //             >>> trip_params.IsValid()
    //             True
    //         "Args:
    //             source (string 'any' | 'first'): Returned route starts at 'any' or 'first' coordinate. (default '')
    //             destination (string 'any' | 'last'): Returned route ends at 'any' or 'last' coordinate. (default '')
    //             roundtrip (bool): Returned route is a roundtrip (route returns to first location). (default True)
    //             RouteParameters (osrm.RouteParameters): Keyword arguments from parent class.
    //         "Returns:
    //             __init__ (osrm.TripParameters): A TripParameters object, for usage in Trip.
    //             IsValid (bool): A bool value denoting validity of parameter values.
    //         "Attributes:
    //             source (string): Returned route starts at 'any' or 'first' coordinate.
    //             destination (string): Returned route ends at 'any' or 'last' coordinate.
    //             roundtrip (bool): Returned route is a roundtrip (route returns to first location).
    //             RouteParameters (osrm.RouteParameters): Attributes from parent class."
    nb::class_<TripParameters, RouteParameters> tp(m, "TripParameters");
        nb::enum_<TripParameters::SourceType>(tp, "SourceType")
            .value("any", TripParameters::SourceType::Any)
            .value("first", TripParameters::SourceType::First);

        nb::enum_<TripParameters::DestinationType>(tp, "DestinationType")
            .value("any", TripParameters::DestinationType::Any)
            .value("last", TripParameters::DestinationType::Last);

        tp.def(nb::init<>())
        .def("__init__", [](TripParameters* t,
                TripParameters::SourceType source,
                TripParameters::DestinationType destination,
                bool roundtrip,
                    const bool steps,
                    int number_of_alternatives,
                    const std::vector<RouteParameters::AnnotationsType>& annotations,
                    RouteParameters::GeometriesType geometries,
                    RouteParameters::OverviewType overview,
                    const std::optional<bool> continue_straight,
                    std::vector<std::size_t> waypoints,
                    std::vector<osrm::util::Coordinate> coordinates,
                    std::vector<std::optional<osrm::engine::Hint>> hints,
                    std::vector<std::optional<double>> radiuses,
                    std::vector<std::optional<osrm::engine::Bearing>> bearings,
                    const std::vector<std::optional<osrm::engine::Approach>>& approaches,
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
                    "continue_straight"_a = std::optional<bool>(),
                    "waypoints"_a = std::vector<std::size_t>(),
                    "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                    "hints"_a = std::vector<std::optional<osrm::engine::Hint>>(),
                    "radiuses"_a = std::vector<std::optional<double>>(),
                    "bearings"_a = std::vector<std::optional<osrm::engine::Bearing>>(),
                    "approaches"_a = std::vector<std::string*>(),
                    "generate_hints"_a = true,
                    "exclude"_a = std::vector<std::string>(),
                    "snapping"_a = std::string()
            )
        .def_rw("source", &TripParameters::source)
        .def_rw("destination", &TripParameters::destination)
        .def_rw("roundtrip", &TripParameters::roundtrip)
        .def("IsValid", &TripParameters::IsValid);
}
