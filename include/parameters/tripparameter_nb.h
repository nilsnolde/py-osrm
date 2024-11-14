#ifndef OSRM_NB_TRIPPARAMETER_H
#define OSRM_NB_TRIPPARAMETER_H

#include "engine/api/trip_parameters.hpp"

#include <nanobind/nanobind.h>

#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

void init_TripParameters(nanobind::module_& m);

#endif //OSRM_NB_TRIPPARAMETER_H
