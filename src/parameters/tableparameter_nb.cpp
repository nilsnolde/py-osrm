#include "parameters/tableparameter_nb.h"

#include "engine/api/table_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TableParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::TableParameters;

    // "Instantiates an instance of TableParameters.
    //         "Examples:
    //             >>> table_params = osrm.TableParameters(
    //                     coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],
    //                     sources = [0],
    //                     destinations = [1],
    //                     annotations = ['duration'],
    //                     fallback_speed = 1,
    //                     fallback_coordinate_type = 'input',
    //                     scale_factor = 0.9
    //                 )
    //             >>> table_params.IsValid()
    //             True
    //         "Args:
    //             sources (list of int): Use location with given index as source. (default [])
    //             destinations (list of int): Use location with given index as destination. (default [])
    //             annotations (list of 'none' | 'duration' | 'distance' | 'all'): \
    //                 Returns additional metadata for each coordinate along the route geometry. (default [])
    //             fallback_speed (float): If no route found between a source/destination pair, calculate the as-the-crow-flies distance, \
    //                 then use this speed to estimate duration. (default INVALID_FALLBACK_SPEED)
    //             fallback_coordinate_type (string 'input' | 'snapped'): When using a fallback_speed, use the user-supplied coordinate (input), \
    //                 or the snapped location (snapped) for calculating distances. (default '')
    //             scale_factor: Scales the table duration values by this number (use in conjunction with annotations=durations). (default 1.0)
    //             BaseParameters (osrm.osrm_ext.BaseParameters): Keyword arguments from parent class.
    //         "Returns:
    //             __init__ (osrm.TableParameters): A TableParameters object, for usage in Table.
    //             IsValid (bool): A bool value denoting validity of parameter values.
    //         "Attributes:
    //             sources (list of int): Use location with given index as source.
    //             destinations (list of int): Use location with given index as destination.
    //             annotations (string): Returns additional metadata for each coordinate along the route geometry.
    //             fallback_speed (float): If no route found between a source/destination pair, calculate the as-the-crow-flies distance, \
    //                 then use this speed to estimate duration.
    //             fallback_coordinate_type (string): When using a fallback_speed, use the user-supplied coordinate (input), \
    //                 or the snapped location (snapped) for calculating distances.
    //             scale_factor: Scales the table duration values by this number (use in conjunction with annotations=durations).
    //             BaseParameters (osrm.osrm_ext.BaseParameters): Attributes from parent class."

    nb::class_<TableParameters, BaseParameters> tp(m, "TableParameters");
        nb::enum_<TableParameters::FallbackCoordinateType>(tp, "FallbackCoordinateType")
            .value("input", TableParameters::FallbackCoordinateType::Input)
            .value("snapped", TableParameters::FallbackCoordinateType::Snapped);

        nb::enum_<TableParameters::AnnotationsType>(tp, "AnnotationsType")
            .value("none", TableParameters::AnnotationsType::None)
            .value("duration", TableParameters::AnnotationsType::Duration)
            .value("distance", TableParameters::AnnotationsType::Distance)
            .value("all", TableParameters::AnnotationsType::All);

        tp.def(nb::init<>())
        .def("__init__", [](TableParameters* t,
                std::vector<std::size_t> sources,
                std::vector<std::size_t> destinations,
                TableParameters::AnnotationsType annotations,
                double fallback_speed,
                TableParameters::FallbackCoordinateType fallback_coordinate_type,
                double scale_factor,
                std::vector<osrm::util::Coordinate> coordinates,
                std::vector<std::optional<osrm::engine::Hint>> hints,
                std::vector<std::optional<double>> radiuses,
                std::vector<std::optional<osrm::engine::Bearing>> bearings,
                const std::vector<std::optional<osrm::engine::Approach>>& approaches,
                bool generate_hints,
                std::vector<std::string> exclude,
                const BaseParameters::SnappingType snapping
            ) {
                new (t) TableParameters();

                t->sources = std::move(sources);
                t->destinations = std::move(destinations);
                t->annotations = annotations;
                t->fallback_speed = fallback_speed;
                t->fallback_coordinate_type = fallback_coordinate_type;
                t->scale_factor = scale_factor;
                
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
                "sources"_a = std::vector<std::size_t>(),
                "destinations"_a = std::vector<std::size_t>(),
                "annotations"_a = TableParameters::AnnotationsType::Duration,
                "fallback_speed"_a = osrm::from_alias<double>(INVALID_FALLBACK_SPEED),
                "fallback_coordinate_type"_a = TableParameters::FallbackCoordinateType::Input,
                "scale_factor"_a = 1.0,
                "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                "hints"_a = std::vector<std::optional<osrm::engine::Hint>>(),
                "radiuses"_a = std::vector<std::optional<double>>(),
                "bearings"_a = std::vector<std::optional<osrm::engine::Bearing>>(),
                "approaches"_a = std::vector<std::optional<osrm::engine::Approach>>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = BaseParameters::SnappingType::Default
            )
        .def_rw("sources", &TableParameters::sources)
        .def_rw("destinations", &TableParameters::destinations)
        .def_rw("fallback_speed", &TableParameters::fallback_speed)
        .def_rw("fallback_coordinate_type", &TableParameters::fallback_coordinate_type)
        .def_rw("annotations", &TableParameters::annotations)
        .def_rw("scale_factor", &TableParameters::scale_factor)
        .def("IsValid", &TableParameters::IsValid);
}
