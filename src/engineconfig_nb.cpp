#include "osrm/engine_config.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;

void init_EngineConfig(nb::module_& m) {
    using osrm::engine::EngineConfig;

    nb::enum_<EngineConfig::Algorithm>(m, "Algorithm")
        .value("CH", EngineConfig::Algorithm::CH)
        .value("CoreCH", EngineConfig::Algorithm::CoreCH)
        .value("MLD", EngineConfig::Algorithm::MLD)
        .export_values();

    nb::class_<EngineConfig>(m, "EngineConfig", nb::is_final())
        .def(nb::init<>())
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
