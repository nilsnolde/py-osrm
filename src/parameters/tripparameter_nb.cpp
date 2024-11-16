#include "parameters/tripparameter_nb.h"

#include "engine/api/trip_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TripParameters(nb::module_& m) {
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::TripParameters;

    nb::class_<TripParameters, RouteParameters> tp(m, "TripParameters");
        tp.doc() =  "TripParameters is an object containing configurations for OSRM trip requests.\n\n"
                    "Attributes:\n"
                    "   - source (TripParameters.SourceType): Returned route starts at 'any' or 'first' coordinate.\n"
                    "   - destination (TripParameters.DestinationType): Returned route ends at 'any' or 'last' coordinate.\n"
                    "   - roundtrip (bool): Returned route is a roundtrip (route returns to first location).\n"
                    "   - RouteParameters (osrm.RouteParameters): Attributes from parent class.\n"
                    "Examples:\n"
                    "    >>> trip_params = osrm.TripParameters(\n"
                    "            coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],\n"
                    "            source = TripParameters.SourceType.any,\n"
                    "            destination = TripParameters.DestinationType.last,\n"
                    "            roundtrip = False\n"
                    "        )\n"
                    "    >>> trip_params.IsValid()\n"
                    "    True\n";
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
                bool steps,
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
                "source"_a = TripParameters::SourceType::Any,
                "destination"_a = TripParameters::DestinationType::Any,
                "roundtrip"_a = true,
                "steps"_a = false,
                "alternatives"_a = 0,
                "annotations"_a = std::vector<RouteParameters::AnnotationsType>(),
                "geometries"_a = RouteParameters::GeometriesType::Polyline,
                "overview"_a = RouteParameters::OverviewType::Simplified,
                "continue_straight"_a = std::optional<bool>(),
                "waypoints"_a = std::vector<std::size_t>(),
                "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                "hints"_a = std::vector<std::optional<osrm::engine::Hint>>(),
                "radiuses"_a = std::vector<std::optional<double>>(),
                "bearings"_a = std::vector<std::optional<osrm::engine::Bearing>>(),
                "approaches"_a = std::vector<std::optional<osrm::engine::Approach>>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = BaseParameters::SnappingType::Default,
                "Instantiates an instance of TripParameters.\n"
                "Args:\n"
                "    - source (TripParameters.SourceType any | first): Returned route starts at 'any' or 'first' coordinate. (default any)\n"
                "    - destination (TripParameters.DestinationType any | last): Returned route ends at 'any' or 'last' coordinate. (default any)\n"
                "    - roundtrip (bool): Returned route is a roundtrip (route returns to first location). (default True)\n"
                "    - RouteParameters (osrm.RouteParameters): Keyword arguments from parent class.\n"
                "Returns:\n"
                "    __init__ (osrm.TripParameters): A TripParameters object, for usage in Trip.\n"
            )
        .def_rw("source", &TripParameters::source)
        .def_rw("destination", &TripParameters::destination)
        .def_rw("roundtrip", &TripParameters::roundtrip)
        .def("IsValid", &TripParameters::IsValid);
}
