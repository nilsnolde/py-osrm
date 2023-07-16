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

    nb::class_<NearestParameters, BaseParameters>(m, "NearestParameters")
        .def("__init__", [](NearestParameters* t,
                std::vector<osrm::util::Coordinate> coordinates,
                std::vector<boost::optional<osrm::engine::Hint>> hints,
                std::vector<boost::optional<double>> radiuses,
                std::vector<boost::optional<osrm::engine::Bearing>> bearings,
                const std::vector<std::string*>& approaches,
                bool generate_hints,
                std::vector<std::string> exclude,
                const std::string& snapping
            ) {
                new (t) NearestParameters();
                
                t->coordinates = std::move(coordinates);
                t->hints = std::move(hints);
                t->radiuses = std::move(radiuses);
                t->bearings = std::move(bearings);
                t->approaches = std::move(osrm_nb_util::get_approach(approaches));
                t->generate_hints = generate_hints;
                t->exclude = std::move(exclude);
                t->snapping = osrm_nb_util::get_snapping_type(snapping);
            },
                "coordinates"_a = std::vector<osrm::util::Coordinate>(),
                "hints"_a = std::vector<boost::optional<osrm::engine::Hint>>(),
                "radiuses"_a = std::vector<boost::optional<double>>(),
                "bearings"_a = std::vector<boost::optional<osrm::engine::Bearing>>(),
                "approaches"_a = std::vector<std::string*>(),
                "generate_hints"_a = true,
                "exclude"_a = std::vector<std::string>(),
                "snapping"_a = std::string()
            )
        .def_rw("number_of_results", &NearestParameters::number_of_results)
        .def("IsValid", &NearestParameters::IsValid);
}
