#include "parameters/routeparameter_nb.h"

#include "engine/api/route_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_RouteParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::RouteParameters;

    nb::class_<RouteParameters, BaseParameters> rp(m, "RouteParameters");
        rp.doc() =  "RouteParameters is an object containing configurations for OSRM route requests.\n\n"
                    "Attributes:\n"
                    "   - steps (bool): Return route steps for each route leg.\n"
                    "   - alternatives (bool): Search for alternative routes.\n"
                    "   - number_of_alternatives (int): Search for n alternative routes.\n"
                    "   - annotations_type (RouteParameters.AnnotationsType): Returns additional metadata for each coordinate along the route geometry.\n"
                    "   - geometries (RouteParameters.GeometriesType): Returned route geometry format - influences overview and per step.\n"
                    "   - overview (RouteParameters.OverviewType): Add overview geometry either full, simplified.\n"
                    "   - continue_straight (bool): Forces the route to keep going straight at waypoints, constraining u-turns.\n"
                    "   - BaseParameters (osrm.osrm_ext.BaseParameters): Attributes from parent class.\n"
                    "Examples:\n"
                    "    >>> route_params = osrm.RouteParameters(\n"
                    "            coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],\n"
                    "            steps = True,\n"
                    "            number_of_alternatives = 3,\n"
                    "            annotations = [RouteParameters.AnnotationsType.speed],\n"
                    "            geometries = RouteParameters.GeometriesType.polyline,\n"
                    "            overview = RouteParameters.OverviewType.simplified,\n"
                    "            continue_straight = False,\n"
                    "            waypoints = [0, 1],\n"
                    "            radiuses = [4.07, 4.07],\n"
                    "            bearings = [(200, 180), (250, 180)],\n"
                    "            generate_hints = False,\n"
                    "            exclude = ['motorway'],\n"
                    "            snapping = BaseParameters.SnappingType.default\n"
                    "        )\n"
                    "    >>> route_params.IsValid()\n"
                    "    True\n";
        nb::enum_<RouteParameters::GeometriesType>(rp, "GeometriesType")
            .value("polyline", RouteParameters::GeometriesType::Polyline)
            .value("polyline6", RouteParameters::GeometriesType::Polyline6)
            .value("geojson", RouteParameters::GeometriesType::GeoJSON);

        nb::enum_<RouteParameters::OverviewType>(rp, "OverviewType")
            .value("simplified", RouteParameters::OverviewType::Simplified)
            .value("full", RouteParameters::OverviewType::Full)
            .value("false", RouteParameters::OverviewType::False);

        nb::enum_<RouteParameters::AnnotationsType>(rp, "AnnotationsType")
            .value("none", RouteParameters::AnnotationsType::None)
            .value("duration", RouteParameters::AnnotationsType::Duration)
            .value("nodes", RouteParameters::AnnotationsType::Nodes)
            .value("distance", RouteParameters::AnnotationsType::Distance)
            .value("weight", RouteParameters::AnnotationsType::Weight)
            .value("datasources", RouteParameters::AnnotationsType::Datasources)
            .value("speed", RouteParameters::AnnotationsType::Speed)
            .value("all", RouteParameters::AnnotationsType::All);

        rp.def(nb::init<>())
        .def("__init__", [](RouteParameters* t,
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
                "number_of_alternatives"_a = 0,
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
                "Instantiates an instance of RouteParameters.\n"
                "Args:\n"
                "    - steps (bool): Return route steps for each route leg. (default False)\n"
                "    - number_of_alternatives (int): Search for n alternative routes. (default 0)\n"
                "    - annotations (list of RouteParameters.AnnotationsType none | duration | nodes | distance | weight | datasources \\n"
                "         | speed | all): Returns additional metadata for each coordinate along the route geometry. (default [] defaults to none)\n"
                "    - geometries (RouteParameters.GeometriesType polyline | polyline6 | geojson): Returned route geometry format - influences overview and per step. (default polyline)\n"
                "    - overview (RouteParameters.OverviewType simplified | full | false): Add overview geometry either full, simplified. (default simplified)\n"
                "    - continue_straight (bool): Forces the route to keep going straight at waypoints, constraining u-turns. (default {})\n"
                "    - waypoints (list of int): Treats input coordinates indicated by given indices as waypoints in returned Match object. (default [])\n"
                "    - BaseParameters (osrm.osrm_ext.BaseParameters): Keyword arguments from parent class.\n"
                "Returns:\n"
                "    __init__ (osrm.RouteParameters): A RouteParameters object, for usage in Route.\n"
            )
        .def_rw("steps", &RouteParameters::steps)
        .def_rw("alternatives", &RouteParameters::alternatives)
        .def_rw("number_of_alternatives", &RouteParameters::number_of_alternatives)
        .def_rw("annotations_type", &RouteParameters::annotations_type)
        .def_rw("geometries", &RouteParameters::geometries)
        .def_rw("overview", &RouteParameters::overview)
        .def_rw("continue_straight", &RouteParameters::continue_straight)
        .def("IsValid", &RouteParameters::IsValid);
}
