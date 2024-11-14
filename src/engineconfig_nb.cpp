#include "engineconfig_nb.h"

#include "osrm/engine_config.hpp"
#include "utility/osrm_utility.h"
#include "utility/param_utility.h"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_EngineConfig(nb::module_& m) {
    using osrm::engine::EngineConfig;

    nb::class_<EngineConfig> ec(m, "EngineConfig", nb::is_final());
        nb::enum_<EngineConfig::Algorithm>(ec, "Algorithm")
            .value("CH", EngineConfig::Algorithm::CH)
            .value("MLD", EngineConfig::Algorithm::MLD);

        ec.def(nb::init<>())
        .def("__init__", [](EngineConfig* t, const nb::kwargs& kwargs) {
            new (t) EngineConfig();

            osrm_nb_util::populate_cfg_from_kwargs(kwargs, *t);

            if(!t->IsValid()) {
                throw std::runtime_error("Config Parameters are Invalid");
            }
        })
        .def("IsValid", &EngineConfig::IsValid)
        .def("SetStorageConfig", [](EngineConfig& self, const std::string& path) {
            self.storage_config = osrm::storage::StorageConfig(path);
        })
        .def_rw("max_locations_trip", &EngineConfig::max_locations_trip)
        .def_rw("max_locations_viaroute", &EngineConfig::max_locations_viaroute)
        .def_rw("max_locations_distance_table", &EngineConfig::max_locations_distance_table)
        .def_rw("max_locations_map_matching", &EngineConfig::max_locations_map_matching)
        .def_rw("max_radius_map_matching", &EngineConfig::max_radius_map_matching)
        .def_rw("max_results_nearest", &EngineConfig::max_results_nearest)
        .def_rw("default_radius", &EngineConfig::default_radius)
        .def_rw("max_alternatives", &EngineConfig::max_alternatives)
        .def_rw("use_shared_memory", &EngineConfig::use_shared_memory)
        .def_rw("memory_file", &EngineConfig::memory_file)
        .def_rw("use_mmap", &EngineConfig::use_mmap)
        .def_rw("algorithm", &EngineConfig::algorithm)
        .def_rw("verbosity", &EngineConfig::verbosity)
        .def_rw("dataset_name", &EngineConfig::dataset_name);
}
