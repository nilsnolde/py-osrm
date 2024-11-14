#ifndef OSRM_NB_ROUTEPARAMETER_H
#define OSRM_NB_ROUTEPARAMETER_H

#include "engine/api/route_parameters.hpp"

#include <nanobind/nanobind.h>

#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/optional.h>

void init_RouteParameters(nanobind::module_& m);

#endif //OSRM_NB_ROUTEPARAMETER_H
