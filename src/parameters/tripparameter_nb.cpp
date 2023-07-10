#include "parameters/tripparameter_nb.h"

#include "engine/api/trip_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TripParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::TripParameters;

    nb::enum_<TripParameters::SourceType>(m, "TripSourceType")
        .value("Any", TripParameters::SourceType::Any)
        .value("First", TripParameters::SourceType::First)
        .export_values();

    nb::enum_<TripParameters::DestinationType>(m, "TripDestinationType")
        .value("Any", TripParameters::DestinationType::Any)
        .value("Last", TripParameters::DestinationType::Last)
        .export_values();

    nb::class_<TripParameters, RouteParameters>(m, "TripParameters")
        .def(nb::init<>())
        .def(nb::init<
                TripParameters::SourceType,
                TripParameters::DestinationType,
                bool,
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
                "source"_a,
                "destination"_a,
                "roundtrip"_a,
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
        .def_rw("source", &TripParameters::source)
        .def_rw("destination", &TripParameters::destination)
        .def_rw("roundtrip", &TripParameters::roundtrip)
        .def("IsValid", &TripParameters::IsValid);
}
