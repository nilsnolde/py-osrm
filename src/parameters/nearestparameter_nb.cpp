#include "parameters/nearestparameter_nb.h"

#include "engine/api/nearest_parameters.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_NearestParameters(nb::module_& m) {
    using osrm::engine::api::BaseParameters;
    using osrm::engine::api::NearestParameters;

    // "Instantiates an instance of NearestParameters.
    //         "Examples:
    //             >>> nearest_params = osrm.NearestParameters(
    //                     coordinates = [(7.41337, 43.72956)],
    //                     exclude = ['motorway']
    //                 )
    //             >>> nearest_params.IsValid()
    //             True
    //         "Args:
    //             BaseParameters (osrm.osrm_ext.BaseParameters): Keyword arguments from parent class.
    //         "Returns:
    //             __init__ (osrm.NearestParameters): A NearestParameters object, for usage in osrm.OSRM.Nearest.
    //             IsValid (bool): A bool value denoting validity of parameter values.
    //         "Attributes:
    //             number_of_results (unsigned int): Number of nearest segments that should be returned.
    //             BaseParameters (osrm.osrm_ext.BaseParameters): Attributes from parent class."

    nb::class_<NearestParameters, BaseParameters>(m, "NearestParameters")
        .def(nb::init<>())
        .def("__init__", [](NearestParameters* t,
                std::vector<osrm::util::Coordinate> coordinates,
                std::vector<std::optional<osrm::engine::Hint>> hints,
                std::vector<std::optional<double>> radiuses,
                std::vector<std::optional<osrm::engine::Bearing>> bearings,
                const std::vector<std::optional<osrm::engine::Approach>>& approaches,
                bool generate_hints,
                std::vector<std::string> exclude,
                const BaseParameters::SnappingType snapping
            ) {
                new (t) NearestParameters();
                
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
                "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                "hints"_a = std::vector<std::optional<osrm::engine::Hint>>(),
                "radiuses"_a = std::vector<std::optional<double>>(),
                "bearings"_a = std::vector<std::optional<osrm::engine::Bearing>>(),
                "approaches"_a = std::vector<std::string*>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = std::string()
            )
        .def_rw("number_of_results", &NearestParameters::number_of_results)
        .def("IsValid", &NearestParameters::IsValid);
}
