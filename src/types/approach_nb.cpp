#include "types/approach_nb.h"

#include "engine/approach.hpp"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_Approach(nb::module_& m) {
    using osrm::engine::Approach;

    nb::enum_<Approach>(m, "Approach")
        .value("curb",Approach::CURB)
        .value("unrestricted",Approach::UNRESTRICTED);
}
