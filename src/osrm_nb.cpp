#include "osrm/osrm.hpp"

#include "osrm/engine_config.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_EngineConfig(nb::module_& m);

NB_MODULE(osrm_ext, m) {
    namespace json = osrm::util::json;
    namespace api = osrm::engine::api;

    using osrm::OSRM;
    using osrm::engine::EngineConfig;

    init_EngineConfig(m);

    nb::class_<OSRM>(m, "OSRM", nb::is_final())
        .def(nb::init<EngineConfig&>());    
}
