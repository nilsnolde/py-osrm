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

    // "Instantiates an instance of OSRM.
    //         "Examples:
    //             >>> import osrm
    //             >>> py_osrm = osrm.OSRM('.tests/test_data/ch/monaco.osrm')
    //             >>> py_osrm = osrm.OSRM(
    //                     algorithm = 'CH',
    //                     storage_config = '.tests/test_data/ch/monaco.osrm',
    //                     max_locations_trip = 3,
    //                     max_locations_viaroute = 3,
    //                     max_locations_distance_table = 3,
    //                     max_locations_map_matching = 3,
    //                     max_results_nearest = 1,
    //                     max_alternatives = 1,
    //                     default_radius = 'unlimited'
    //                 )
    //         "Args:
    //             storage_config (string): File path string to storage config.
    //             EngineConfig (osrm.osrm_ext.EngineConfig): Keyword arguments from the EngineConfig class.
    //         "Returns:
    //             __init__ (osrm.OSRM): A OSRM object.
    //         "Raises:
    //             RuntimeError: On invalid OSRM EngineConfig parameters."

    nb::class_<OSRM>(m, "OSRM", nb::is_final())
        .def(nb::init<EngineConfig&>())
        .def("__init__", [](OSRM* t, const std::string& storage_path, const nb::kwargs& kwargs) { 
            EngineConfig config;
            osrm_nb_util::populate_cfg_from_kwargs(kwargs, config);
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

            // "Matches/snaps given GPS points to the road network in the most plausible way."
            // "Examples:
            //     >>> res = py_osrm.Match(match_params)"
            // "Args:
            //     match_params (osrm.MatchParameters): MatchParameters Object."
            // "Returns:
            //     (json): [A Match JSON Response](https://project-osrm.org/docs/v5.24.0/api/#match-service)."
            // "Raises:
            //     RuntimeError: On invalid MatchParameters."

            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Match Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Match(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Nearest", [](OSRM* t, const NearestParameters& params) {

            // "Snaps a coordinate to the street network and returns the nearest matches."
            // "Examples:
            //     >>> res = py_osrm.Nearest(nearest_params)"
            // "Args:
            //     nearest_params (osrm.NearestParameters): NearestParameters Object."
            // "Returns:
            //     (json): [A Nearest JSON Response](https://project-osrm.org/docs/v5.24.0/api/#nearest-service)."
            // "Raises:
            //     RuntimeError: On invalid NearestParameters."

            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Nearest Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Nearest(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Route", [](OSRM* t, const RouteParameters& params) {

            // "Finds the fastest route between coordinates in the supplied order."
            // "Examples:
            //     >>> res = py_osrm.Route(route_params)"
            // "Args:
            //     route_params (osrm.RouteParameters): RouteParameters Object."
            // "Returns:
            //     (json): [A Route JSON Response](https://project-osrm.org/docs/v5.24.0/api/#route-service)."
            // "Raises:
            //     RuntimeError: On invalid RouteParameters."

            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Route Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Route(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Table", [](OSRM* t, const TableParameters& params) {

            // "Computes the duration of the fastest route between all pairs of supplied coordinates."
            // "Examples:
            //     >>> res = py_osrm.Table(table_params)"
            // "Args:
            //     table_params (osrm.TableParameters): TableParameters Object."
            // "Returns:
            //     (json): [A Table JSON Response](https://project-osrm.org/docs/v5.24.0/api/#table-service)."
            // "Raises:
            //     RuntimeError: On invalid TableParameters."

            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Table Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Table(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        })
        .def("Tile", [](OSRM* t, const TileParameters& params) {

            // "Computes the duration of the fastest route between all pairs of supplied coordinates."
            // "Examples:
            //     >>> res = py_osrm.Tile(tile_params)"
            // "Args:
            //     tile_params (osrm.TileParameters): TileParameters Object."
            // "Returns:
            //     (json): [A Tile JSON Response](https://project-osrm.org/docs/v5.24.0/api/#tile-service)."
            // "Raises:
            //     RuntimeError: On invalid TileParameters."

            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Tile Parameters");
            }

            std::string result;
            osrm::engine::Status status = t->Tile(params, result);
            nb::object obj = nb::bytes(result.c_str(), result.size());

            return obj;
        })
        .def("Trip", [](OSRM* t, const TripParameters& params) {

            // "Solves the Traveling Salesman Problem using a greedy heuristic (farthest-insertion algorithm)."
            // "Examples:
            //     >>> res = py_osrm.Trip(trip_params)"
            // "Args:
            //     trip_params (osrm.TripParameters): TripParameters Object."
            // "Returns:
            //     (json): [A Trip JSON Response](https://project-osrm.org/docs/v5.24.0/api/#trip-service)."
            // "Raises:
            //     RuntimeError: On invalid TripParameters."

            if(!params.IsValid()) {
                throw std::runtime_error("Invalid Trip Parameters");
            }

            json::Object result;
            osrm::engine::Status status = t->Trip(params, result);
            osrm_nb_util::check_status(status, result);

            return result;
        });
}
