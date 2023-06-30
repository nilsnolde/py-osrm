#include "types/approach_nb.h"

#include "engine/approach.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_Approach(nb::module_& m) {
    using osrm::engine::Approach;

    nb::enum_<Approach>(m, "Approach")
        .value("CURB", Approach::CURB)
        .value("UNRESTRICTED", Approach::UNRESTRICTED)
        .export_values();
}
