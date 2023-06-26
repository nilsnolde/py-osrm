#include "osrm/osrm.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/route_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "engineconfig_nb.h"
#include "utility/osrm_kwargs.h"
#include "types/approach_nb.h"
#include "types/bearing_nb.h"
#include "types/coordinate_nb.h"
#include "types/jsoncontainer_nb.h"
#include "types/optional_nb.h"
#include "types/status_nb.h"
#include "parameters/baseparameter_nb.h"
#include "parameters/routeparameter_nb.h"

namespace nb = nanobind;

NB_MODULE(osrm_ext, m) {
    namespace api = osrm::engine::api;
    namespace json = osrm::util::json;

    using osrm::OSRM;
    using osrm::engine::EngineConfig;
    using osrm::engine::api::RouteParameters;

    init_EngineConfig(m);

    init_Approach(m);
    init_Bearing(m);
    init_Coordinate(m);
    init_JSONContainer(m);
    init_Optional(m);
    init_Status(m);

    init_BaseParameters(m);
    init_RouteParameters(m);

    nb::class_<OSRM>(m, "OSRM", nb::is_final())
        .def(nb::init<EngineConfig&>())
        .def("__init__", [](OSRM* t, const std::string& storage_path) { 
            EngineConfig config;
            config.storage_config = osrm::storage::StorageConfig(storage_path);

            new (t) OSRM(config);
        })
        .def("__init__", [](OSRM* t, const nb::kwargs& kwargs) {
            EngineConfig config;
            osrm_nb_util::populate_cfg_from_kwargs(kwargs, config);

            new (t) OSRM(config);
        })
        .def("Route", nb::overload_cast<const RouteParameters&, json::Object&>(&OSRM::Route, nb::const_))
        .def("Route", nb::overload_cast<const RouteParameters&, api::ResultT&>(&OSRM::Route, nb::const_));
}
