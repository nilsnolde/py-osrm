#include "utility/osrm_kwargs.h"

#include "osrm/osrm.hpp"
#include "osrm/engine_config.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <unordered_map>

namespace nb = nanobind;

using osrm::engine::EngineConfig;

template<typename T>
void assign_val(T& to_assign, nb::handle& val) {
    to_assign = nb::cast<T>(val);
}

namespace osrm_nb_util {

void populate_cfg_from_kwargs(const nb::kwargs& kwargs, EngineConfig& config) {
    std::unordered_map<std::string, std::function<void(nb::handle&)>> assign_map {
        { "storage_config", [&config](nb::handle& val) {
            std::string temp;
            assign_val(temp, val);
            config.storage_config = osrm::storage::StorageConfig(temp);
        } },
        { "max_locations_trip", [&config](nb::handle& val) {
            assign_val(config.max_locations_trip, val);
        } },
        { "max_locations_viaroute", [&config](nb::handle& val) {
            assign_val(config.max_locations_viaroute, val);
        } },
        { "max_locations_distance_table", [&config](nb::handle& val) {
            assign_val(config.max_locations_distance_table, val);
        } },
        { "max_locations_map_matching", [&config](nb::handle& val) {
            assign_val(config.max_locations_map_matching, val);
        } },
        { "max_radius_map_matching", [&config](nb::handle& val) {
            assign_val(config.max_radius_map_matching, val);
        } },
        { "max_results_nearest", [&config](nb::handle& val) {
            assign_val(config.max_results_nearest, val);
        } },
        { "default_radius", [&config](nb::handle& val) {
            assign_val(config.default_radius.get(), val);
        } },
        { "max_alternatives", [&config](nb::handle& val) {
            assign_val(config.max_alternatives, val);
        } },
        { "use_shared_memory", [&config](nb::handle& val) {
            assign_val(config.use_shared_memory, val);
        } },
        { "memory_file", [&config](nb::handle& val) {
            std::string temp;
            assign_val(temp, val);
            config.memory_file = boost::filesystem::path(temp);
        } },
        { "use_mmap", [&config](nb::handle& val) {
            assign_val(config.use_mmap, val);
        } },
        { "algorithm", [&config](nb::handle& val) {
            std::string algorithm_string;
            assign_val(algorithm_string, val);

            if(algorithm_string == "CH" || algorithm_string == "ch") {
                config.algorithm = EngineConfig::Algorithm::CH;
            }
            else if(algorithm_string == "CoreCH" || algorithm_string == "corech") {
                config.algorithm = EngineConfig::Algorithm::CoreCH;
            }
            else if(algorithm_string == "MLD" || algorithm_string == "mld") {
                config.algorithm = EngineConfig::Algorithm::MLD;
            }
            else {
                throw std::invalid_argument(algorithm_string);
            }
        } },
        { "verbosity", [&config](nb::handle& val) {
            assign_val(config.verbosity, val);
        } },
        { "dataset_name", [&config](nb::handle& val) {
            assign_val(config.dataset_name, val);
        } }
    };

    for(auto kwarg : kwargs) {
        const std::string arg_str = nb::cast<std::string>(kwarg.first);
        auto itr = assign_map.find(arg_str);

        if(itr == assign_map.end()) {
            throw std::invalid_argument(arg_str);
        }
        
        itr->second(kwarg.second);
    }
}

} //namespace osrm_nb_util