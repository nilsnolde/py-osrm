#include "osrm/osrm.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/match_parameters.hpp"
#include "osrm/nearest_parameters.hpp"
#include "osrm/route_parameters.hpp"
#include "osrm/table_parameters.hpp"
#include "osrm/tile_parameters.hpp"
#include "osrm/trip_parameters.hpp"

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
#include "parameters/matchparameter_nb.h"
#include "parameters/nearestparameter_nb.h"
#include "parameters/routeparameter_nb.h"
#include "parameters/tableparameter_nb.h"
#include "parameters/tileparameter_nb.h"
#include "parameters/tripparameter_nb.h"

namespace nb = nanobind;

NB_MODULE(osrm_ext, m) {
    namespace api = osrm::engine::api;
    namespace json = osrm::util::json;

    using osrm::OSRM;
    using osrm::engine::EngineConfig;
    using osrm::engine::api::MatchParameters;
    using osrm::engine::api::NearestParameters;
    using osrm::engine::api::RouteParameters;
    using osrm::engine::api::TableParameters;
    using osrm::engine::api::TileParameters;
    using osrm::engine::api::TripParameters;

    init_EngineConfig(m);

    init_Approach(m);
    init_Bearing(m);
    init_Coordinate(m);
    init_JSONContainer(m);
    init_Optional(m);
    init_Status(m);

    init_BaseParameters(m);
    // init_MatchParameters(m);
    init_NearestParameters(m);
    init_RouteParameters(m);
    init_TableParameters(m);
    init_TileParameters(m);
    init_TripParameters(m);

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
        // .def("Match", nb::overload_cast<const MatchParameters&, json::Object&>(&OSRM::Match, nb::const_))
        // .def("Match", nb::overload_cast<const MatchParameters&, api::ResultT&>(&OSRM::Match, nb::const_))
        .def("Nearest", nb::overload_cast<const NearestParameters&, json::Object&>(&OSRM::Nearest, nb::const_))
        .def("Nearest", nb::overload_cast<const NearestParameters&, api::ResultT&>(&OSRM::Nearest, nb::const_))
        .def("Route", nb::overload_cast<const RouteParameters&, json::Object&>(&OSRM::Route, nb::const_))
        .def("Route", nb::overload_cast<const RouteParameters&, api::ResultT&>(&OSRM::Route, nb::const_))
        .def("Table", nb::overload_cast<const TableParameters&, json::Object&>(&OSRM::Table, nb::const_))
        .def("Table", nb::overload_cast<const TableParameters&, api::ResultT&>(&OSRM::Table, nb::const_))
        .def("Tile", nb::overload_cast<const TileParameters&, std::string&>(&OSRM::Tile, nb::const_))
        .def("Tile", nb::overload_cast<const TileParameters&, api::ResultT&>(&OSRM::Tile, nb::const_))
        .def("Trip", nb::overload_cast<const TripParameters&, json::Object&>(&OSRM::Trip, nb::const_))
        .def("Trip", nb::overload_cast<const TripParameters&, api::ResultT&>(&OSRM::Trip, nb::const_));
}
