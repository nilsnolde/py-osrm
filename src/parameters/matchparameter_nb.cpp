#include "parameters/matchparameter_nb.h"

#include "engine/api/match_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_MatchParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::MatchParameters;

    nb::enum_<MatchParameters::GapsType>(m, "MatchGapsType")
        .value("Split", MatchParameters::GapsType::Split)
        .value("Ignore", MatchParameters::GapsType::Ignore)
        .export_values();

    nb::class_<MatchParameters, RouteParameters>(m, "MatchParameters")
        .def(nb::init<>())
        .def("__init__", [](MatchParameters* t,
            std::vector<unsigned> timestamps,
            MatchParameters::GapsType gaps,
            bool tidy,
            std::vector<std::size_t> waypoints,
                const bool steps,
                int number_of_alternatives,
                const std::vector<RouteParameters::AnnotationsType>& annotations,
                const RouteParameters::GeometriesType geometries,
                const RouteParameters::OverviewType overview,
                const boost::optional<bool> continue_straight,
                    std::vector<osrm::util::Coordinate> coordinates,
                    std::vector<boost::optional<osrm::engine::Hint>> hints,
                    std::vector<boost::optional<double>> radiuses,
                    std::vector<boost::optional<osrm::engine::Bearing>> bearings,
                    std::vector<boost::optional<osrm::engine::Approach>> approaches,
                    bool generate_hints,
                    std::vector<std::string> exclude,
                    const BaseParameters::SnappingType snapping
            ) {
                new (t) MatchParameters();

                t->timestamps = std::move(timestamps);
                t->gaps = gaps;
                t->tidy = tidy;
                t->waypoints = std::move(waypoints);

                t->steps = steps;
                t->alternatives = (bool)number_of_alternatives;
                t->number_of_alternatives = number_of_alternatives;
                t->annotations = !annotations.empty();
                for(int i = 0; i < annotations.size(); ++i) {
                    t->annotations_type = t->annotations_type | annotations[i];
                }           
                t->geometries = geometries;
                t->overview = overview;
                t->continue_straight = continue_straight;
        
                t->coordinates = std::move(coordinates);
                t->hints = std::move(hints);
                t->radiuses = std::move(radiuses);
                t->bearings = std::move(bearings);
                t->approaches = std::move(approaches);
                t->generate_hints = generate_hints;
                t->exclude = std::move(exclude);
                t->snapping = snapping;
            },
                "timestamps"_a,
                "gaps"_a = MatchParameters::GapsType::Split,
                "tidy"_a = false,
                "waypoints"_a = std::vector<std::size_t>(),
                    "steps"_a,
                    "alternatives"_a,
                    "annotations"_a = std::vector<RouteParameters::AnnotationsType>(),
                    "geometries"_a,
                    "overview"_a,
                    "continue_straight"_a,
                        "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                        "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                        "radiuses"_a = std::vector<boost::optional<double>>(),
                        "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                        "approaches"_a = std::vector<boost::optional<osrm::engine::Approach>>(),
                        "generate_hints"_a = true,
                        "exclude"_a = std::vector<std::string>(),
                        "snapping"_a = BaseParameters::SnappingType::Default
            )
        .def_rw("timestamps", &MatchParameters::timestamps)
        .def_rw("gaps", &MatchParameters::gaps)
        .def_rw("tidy", &MatchParameters::tidy)
        .def("IsValid", &MatchParameters::IsValid);
}
