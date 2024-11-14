#ifndef OSRM_NB_TABLEPARAMETER_H
#define OSRM_NB_TABLEPARAMETER_H

#include "engine/api/table_parameters.hpp"

#include <nanobind/nanobind.h>

#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

void init_TableParameters(nanobind::module_& m);

#endif //OSRM_NB_TABLEPARAMETER_H
