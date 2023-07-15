#include "osrm/osrm.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/status.hpp"
#include "osrm/match_parameters.hpp"
#include "osrm/nearest_parameters.hpp"
#include "osrm/route_parameters.hpp"
#include "osrm/table_parameters.hpp"
#include "osrm/tile_parameters.hpp"
#include "osrm/trip_parameters.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <stdexcept>

#include "engineconfig_nb.h"
#include "utility/osrm_utility.h"
#include "types/approach_nb.h"
#include "types/bearing_nb.h"
#include "types/coordinate_nb.h"
#include "types/jsoncontainer_nb.h"
#include "types/optional_nb.h"
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

    init_BaseParameters(m);
    init_NearestParameters(m);
    init_TableParameters(m);
    init_RouteParameters(m);
    init_MatchParameters(m);
    init_TripParameters(m);
    init_TileParameters(m);

    nb::class_<OSRM>(m, "OSRM", nb::is_final())
        .def(nb::init<EngineConfig&>())
        .def("__init__", [](OSRM* t, const std::string& storage_path) { 
            EngineConfig config;
            config.storage_config = osrm::storage::StorageConfig(storage_path);

            if(!config.IsValid()) {
                throw std::runtime_error("Required files are missing");
            }

            new (t) OSRM(config);
        })
        .def("__init__", [](OSRM* t, const nb::kwargs& kwargs) {
            EngineConfig config;
            osrm_nb_util::populate_cfg_from_kwargs(kwargs, config);

            if(!config.IsValid()) {
                throw std::runtime_error("Config Parameters are Invalid");
            }

            new (t) OSRM(config);
        })
        .def("Match", [](OSRM* t, const MatchParameters& params) {
            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Match Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Match(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Nearest", [](OSRM* t, const NearestParameters& params) {
            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Nearest Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Nearest(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Route", [](OSRM* t, const RouteParameters& params) {
            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Route Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Route(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Table", [](OSRM* t, const TableParameters& params) {
            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Table Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Table(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Tile", [](OSRM* t, const TileParameters& params) {
            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Tile Parameters");
            }

            std::string result;
            osrm::engine::Status status = t->Tile(params, result);
            nb::object obj = nb::bytes(result.c_str());

            return obj;
        })
        .def("Trip", [](OSRM* t, const TripParameters& params) {
            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Trip Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Trip(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        });
}
