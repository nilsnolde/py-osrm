#include "osrm/engine_config.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

namespace osrm_nb_util {

void populate_cfg_from_kwargs(const nb::kwargs& kwargs, osrm::engine::EngineConfig& config);

} //namespace osrm_nb_util