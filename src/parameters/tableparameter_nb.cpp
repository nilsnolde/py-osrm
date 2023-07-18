#include "parameters/tableparameter_nb.h"

#include "engine/api/table_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TableParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::TableParameters;

    nb::class_<TableParameters, BaseParameters>(m, "TableParameters")
        .def(nb::init<>())
        .def("__init__", [](TableParameters* t,
                std::vector<std::size_t> sources,
                std::vector<std::size_t> destinations,
                const std::vector<TableParameters::AnnotationsType>& annotations,
                double fallback_speed,
                TableParameters::FallbackCoordinateType fallback_coordinate_type,
                double scale_factor,
                    std::vector<osrm::util::Coordinate> coordinates,
                    std::vector<boost::optional<osrm::engine::Hint>> hints,
                    std::vector<boost::optional<double>> radiuses,
                    std::vector<boost::optional<osrm::engine::Bearing>> bearings,
                    const std::vector<boost::optional<osrm::engine::Approach>>& approaches,
                    bool generate_hints,
                    std::vector<std::string> exclude,
                    const BaseParameters::SnappingType snapping
            ) {
                new (t) TableParameters();

                t->sources = std::move(sources);
                t->destinations = std::move(destinations);
                t->annotations = osrm_nb_util::calculate_tableannotations_type(annotations);
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
                "annotations"_a = std::vector<std::string>(),
                "fallback_speed"_a = osrm::from_alias<double>(INVALID_FALLBACK_SPEED),
                "fallback_coordinate_type"_a = std::string(),
                "scale_factor"_a = 1.0,
                    "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                    "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                    "radiuses"_a = std::vector<boost::optional<double>>(),
                    "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                    "approaches"_a = std::vector<std::string*>(),
                    "generate_hints"_a = true,
                    "exclude"_a = std::vector<std::string>(),
                    "snapping"_a = std::string()
            )
        .def_rw("sources", &TableParameters::sources)
        .def_rw("destinations", &TableParameters::destinations)
        .def_rw("fallback_speed", &TableParameters::fallback_speed)
        .def_rw("fallback_coordinate_type", &TableParameters::fallback_coordinate_type)
        .def_rw("annotations", &TableParameters::annotations)
        .def_rw("scale_factor", &TableParameters::scale_factor)
        .def("IsValid", &TableParameters::IsValid);

    nb::class_<TableParameters::FallbackCoordinateType>(m, "TableFallbackCoordinateType")
        .def("__init__", [](TableParameters::FallbackCoordinateType* t, const std::string& str) {
            TableParameters::FallbackCoordinateType fallback = osrm_nb_util::str_to_enum(str, "TableFallbackCoordinateType", fallback_map);
            new (t) TableParameters::FallbackCoordinateType(fallback);
        })
        .def("__repr__", [](TableParameters::FallbackCoordinateType type) {
            return osrm_nb_util::enum_to_str(type, "TableFallbackCoordinateType", fallback_map);
        });
    nb::implicitly_convertible<std::string, TableParameters::FallbackCoordinateType>();

    nb::class_<TableParameters::AnnotationsType>(m, "TableAnnotationsType")
        .def("__init__", [](TableParameters::AnnotationsType* t, const std::string& str) {
            TableParameters::AnnotationsType annotation = osrm_nb_util::str_to_enum(str, "TableAnnotationsType", table_annotations_map);
            new (t) TableParameters::AnnotationsType(annotation);
        })
        .def("__repr__", [](TableParameters::AnnotationsType type) {
            return std::to_string((int)type);
        })
        .def("__and__", [](TableParameters::AnnotationsType lhs, TableParameters::AnnotationsType rhs) {
            return lhs & rhs;
        }, nb::is_operator())
        .def("__or__", [](TableParameters::AnnotationsType lhs, TableParameters::AnnotationsType rhs) {
            return lhs | rhs;
        }, nb::is_operator())
        .def("__ior__", [](TableParameters::AnnotationsType& lhs, TableParameters::AnnotationsType rhs) {
            return lhs = lhs | rhs;
        }, nb::is_operator());
    nb::implicitly_convertible<std::string, TableParameters::AnnotationsType>();
}
