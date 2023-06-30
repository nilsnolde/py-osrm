#include "parameters/tableparameter_nb.h"

#include "engine/api/table_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_TableParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::TableParameters;

    nb::enum_<TableParameters::FallbackCoordinateType>(m, "TableFallbackCoordinateType", nb::is_arithmetic())
        .value("Input", TableParameters::FallbackCoordinateType::Input)
        .value("Snapped", TableParameters::FallbackCoordinateType::Snapped)
        .export_values();

    nb::enum_<TableParameters::AnnotationsType>(m, "TableAnnotationsType", nb::is_arithmetic())
        .value("None_", TableParameters::AnnotationsType::None)
        .value("Duration", TableParameters::AnnotationsType::Duration)
        .value("Distance", TableParameters::AnnotationsType::Distance)
        .value("All", TableParameters::AnnotationsType::All)
        .export_values();

    nb::class_<TableParameters, BaseParameters>(m, "TableParameters")
        .def(nb::init<>())
        .def(nb::init<
                std::vector<std::size_t>,
                std::vector<std::size_t>,
                const TableParameters::AnnotationsType,
                    std::vector<osrm::util::Coordinate>,
                    std::vector<boost::optional<osrm::engine::Hint>>,
                    std::vector<boost::optional<double>>,
                    std::vector<boost::optional<osrm::engine::Bearing>>,
                    std::vector<boost::optional<osrm::engine::Approach>>,
                    bool,
                    std::vector<std::string>,
                    const BaseParameters::SnappingType
            >(),
                "sources"_a,
                "destinations"_a,
                "annotations"_a = TableParameters::AnnotationsType::Duration,
                    "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                    "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                    "radiuses"_a = std::vector<boost::optional<double>>(),
                    "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                    "approaches"_a = std::vector<boost::optional<osrm::engine::Approach>>(),
                    "generate_hints"_a = true,
                    "exclude"_a = std::vector<std::string>(),
                    "snapping"_a = BaseParameters::SnappingType::Default
            )
        .def(nb::init<
                std::vector<std::size_t>,
                std::vector<std::size_t>,
                const TableParameters::AnnotationsType,
                double,
                TableParameters::FallbackCoordinateType,
                double,
                    std::vector<osrm::util::Coordinate>,
                    std::vector<boost::optional<osrm::engine::Hint>>,
                    std::vector<boost::optional<double>>,
                    std::vector<boost::optional<osrm::engine::Bearing>>,
                    std::vector<boost::optional<osrm::engine::Approach>>,
                    bool,
                    std::vector<std::string>,
                    const BaseParameters::SnappingType
            >(),
                "sources"_a,
                "destinations"_a,
                "annotations"_a = TableParameters::AnnotationsType::Duration,
                "fallback_speed"_a,
                "fallback_coordinate_type"_a = TableParameters::FallbackCoordinateType::Input,
                "scale_factor"_a = 1.0,
                    "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                    "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                    "radiuses"_a = std::vector<boost::optional<double>>(),
                    "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                    "approaches"_a = std::vector<boost::optional<osrm::engine::Approach>>(),
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
        .def("IsValid", &TableParameters::IsValid)
        .def("__and__", [](TableParameters::AnnotationsType lhs, TableParameters::AnnotationsType rhs) {
            return static_cast<bool>(
                static_cast<std::underlying_type_t<TableParameters::AnnotationsType>>(lhs) &
                static_cast<std::underlying_type_t<TableParameters::AnnotationsType>>(rhs));
        }, nb::is_operator())
        .def("__or__", [](TableParameters::AnnotationsType lhs, TableParameters::AnnotationsType rhs) {
            return (TableParameters::AnnotationsType)(
                static_cast<std::underlying_type_t<TableParameters::AnnotationsType>>(lhs) |
                static_cast<std::underlying_type_t<TableParameters::AnnotationsType>>(rhs));
        }, nb::is_operator())
        .def("__ior__", [](TableParameters::AnnotationsType lhs, TableParameters::AnnotationsType rhs) {
            return lhs = lhs | rhs;
        }, nb::is_operator());
}
