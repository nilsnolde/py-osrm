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

    nb::class_<NearestParameters, BaseParameters> np(m, "NearestParameters");
        np.doc() = "NearestParameters is an object containing configurations for OSRM nearest requests.\n\n"
                    "Attributes:\n"
                    "   - number_of_results (unsigned int): Number of nearest segments that should be returned.\n"
                    "   - BaseParameters (osrm.BaseParameters): Attributes from parent class."
                    "Examples:\n"
                    ">>> nearest_params = osrm.NearestParameters(\n"
                    "        coordinates = [(7.41337, 43.72956)],\n"
                    "        exclude = ['motorway']\n"
                    "    )\n"
                    ">>> nearest_params.IsValid()\n"
                    "True\n";
        np.def(nb::init<>())
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
                "approaches"_a = std::vector<std::optional<osrm::engine::Approach>>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = BaseParameters::SnappingType::Default,
                "Instantiates an instance of NearestParameters.\n"
                "Args:\n"
                "   - BaseParameters (osrm.BaseParameters): Keyword arguments from parent class.\n"
                "Returns:\n"
                "   __init__ (osrm.NearestParameters): A NearestParameters object, for usage in osrm.OSRM.Nearest.\n"
            )
        .def_rw("number_of_results", &NearestParameters::number_of_results)
        .def("IsValid", &NearestParameters::IsValid);
}
