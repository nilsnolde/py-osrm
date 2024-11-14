#ifndef OSRM_NB_MATCHPARAMETER_H
#define OSRM_NB_MATCHPARAMETER_H

#include "engine/api/match_parameters.hpp"

#include <nanobind/nanobind.h>

#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

void init_MatchParameters(nanobind::module_& m);

#endif //OSRM_NB_MATCHPARAMETER_H
