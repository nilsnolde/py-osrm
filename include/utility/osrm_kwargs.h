#ifndef OSRM_NB_UTIL_KWARGS_H
#define OSRM_NB_UTIL_KWARGS_H

#include "osrm/engine_config.hpp"

#include <nanobind/nanobind.h>

namespace osrm_nb_util {

void populate_cfg_from_kwargs(const nanobind::kwargs& kwargs, osrm::engine::EngineConfig& config);

} //namespace osrm_nb_util

#endif //OSRM_NB_UTIL_KWARGS_H
