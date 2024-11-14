#include "parameters/baseparameter_nb.h"

#include "engine/api/base_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_BaseParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;

    // "Instantiates an instance of BaseParameters.
    //         "Note:
    //             This is the parent class to many parameter classes, and not intended to be used on its own.
    //         "Args:
    //             coordinates (list of floats pairs): Pairs of Longitude and Latitude Coordinates. (default [])
    //             hints (list): Hint from previous request to derive position in street network. (default [])
    //             radiuses (list of floats): Limits the search to given radius in meters. (default [])
    //             bearings (list of int pairs): Limits the search to segments with given bearing in degrees towards true north in clockwise direction. (default [])
    //             approaches (list): Keep waypoints on curb side. (default [])
    //             generate_hints (bool): Adds a hint to the response which can be used in subsequent requests. (default True)
    //             exclude (list of strings): Additive list of classes to avoid. (default [])
    //             snapping (string 'default' | 'any'): 'default' snapping avoids is_startpoint edges, 'any' will snap to any edge in the graph. (default '')
    //         "Returns:
    //             __init__ (py_osrm.osrm_ext.BaseParameters): A BaseParameter object, that is the parent object to many other Parameter objects.
    //             IsValid (bool): A bool value denoting validity of parameter values.
    //         "Attributes:
    //             coordinates (list of floats pairs): Pairs of longitude & latitude coordinates.
    //             hints (list): Hint from previous request to derive position in street network.
    //             radiuses (list of floats): Limits the search to given radius in meters.
    //             bearings (list of int pairs): Limits the search to segments with given bearing in degrees towards true north in clockwise direction.
    //             approaches (list): Keep waypoints on curb side.
    //             exclude (list of strings): Additive list of classes to avoid, order does not matter.
    //             format (string): Specifies response type - currently only 'json' is supported.
    //             generate_hints (bool): Adds a hint to the response which can be used in subsequent requests.
    //             skip_waypoints (list): Removes waypoints from the response.
    //             snapping (string): 'default' snapping avoids is_startpoint edges, 'any' will snap to any edge in the graph."
            
    nb::class_<BaseParameters> bp(m, "BaseParameters");
        nb::enum_<BaseParameters::SnappingType>(bp, "SnappingType")
            .value("default", BaseParameters::SnappingType::Default)
            .value("any", BaseParameters::SnappingType::Any);

        nb::enum_<BaseParameters::OutputFormatType>(bp, "OutputFormatType")
            .value("json", BaseParameters::OutputFormatType::JSON)
            .value("flatbuffers", BaseParameters::OutputFormatType::FLATBUFFERS);
            
        bp.def(nb::init<>())
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
