#include "parameters/tripparameter_nb.h"

#include "engine/api/trip_parameters.hpp"
#include "utility/param_utility.h"

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
        .def("__init__", [](TripParameters* t,
                const std::string& source,
                const std::string& destination,
                bool,
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
                new (t) TripParameters();

                t->source = osrm_nb_util::get_tripsource_type(source);
                t->destination = osrm_nb_util::get_tripdestination_type(destination);

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
                "source"_a = std::string(),
                "destination"_a = std::string(),
                "roundtrip"_a = true,
                    "steps"_a = false,
                    "alternatives"_a = 0,
                    "annotations"_a = std::vector<RouteParameters::AnnotationsType>(),
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
}
