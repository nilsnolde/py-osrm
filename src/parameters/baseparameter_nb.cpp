#include "parameters/baseparameter_nb.h"

#include "engine/api/base_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_BaseParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;

    nb::class_<BaseParameters> bp(m, "BaseParameters");
        bp.doc() = "This is the parent class to many parameter classes, and not intended to be used on its own.\n\n"
                    "Attributes:\n"
                    "   - coordinates (list of floats pairs | osrm.Coordinate): Pairs of longitude & latitude coordinates.\n"
                    "   - hints (list): Hint from previous request to derive position in street network.\n"
                    "   - radiuses (list of floats): Limits the search to given radius in meters.\n"
                    "   - bearings (list of int pairs | osrm.Bearing): Limits the search to segments with given bearing in degrees towards true north in clockwise direction.\n"
                    "   - approaches (list of osrm.Approach): Keep waypoints on curb side.\n"
                    "   - exclude (list of strings): Additive list of classes to avoid, order does not matter.\n"
                    "   - format (string): Specifies response type - currently only 'json' is supported.\n"
                    "   - generate_hints (bool): Adds a hint to the response which can be used in subsequent requests.\n"
                    "   - skip_waypoints (list): Removes waypoints from the response.\n"
                    "   - snapping (BaseParameters.SnappingType): 'default' snapping avoids is_startpoint edges, 'any' will snap to any edge in the graph.\n";
        nb::enum_<BaseParameters::SnappingType>(bp, "SnappingType")
            .value("default", BaseParameters::SnappingType::Default)
            .value("any", BaseParameters::SnappingType::Any);

        nb::enum_<BaseParameters::OutputFormatType>(bp, "OutputFormatType")
            .value("json", BaseParameters::OutputFormatType::JSON)
            .value("flatbuffers", BaseParameters::OutputFormatType::FLATBUFFERS);
            
        bp.def(nb::init<>(),
            "Instantiates an instance of BaseParameters.\n"
            "Returns:\n"
            "    __init__ (py_osrm.osrm_ext.BaseParameters): A BaseParameter object, that is the parent object to many other Parameter objects.\n"
            )
        .def_rw("coordinates", &BaseParameters::coordinates)
        .def_rw("hints", &BaseParameters::hints)
        .def_rw("radiuses", &BaseParameters::radiuses)
        .def_rw("bearings", &BaseParameters::bearings)
        .def_rw("approaches", &BaseParameters::approaches)
        .def_rw("exclude", &BaseParameters::exclude)
        .def_rw("format", &BaseParameters::format)
        .def_rw("generate_hints", &BaseParameters::generate_hints)
        .def_rw("skip_waypoints", &BaseParameters::skip_waypoints)
        .def_rw("snapping", &BaseParameters::snapping)
        .def("IsValid", &BaseParameters::IsValid);
}
