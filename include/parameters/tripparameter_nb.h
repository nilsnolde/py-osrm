#ifndef OSRM_NB_TRIPPARAMETER_H
#define OSRM_NB_TRIPPARAMETER_H

#include "engine/api/trip_parameters.hpp"

#include <nanobind/nanobind.h>

#include <unordered_map>

using osrm::engine::api::TripParameters;

void init_TripParameters(nanobind::module_& m);

static const std::unordered_map<std::string, TripParameters::SourceType> source_map {
    { "any", TripParameters::SourceType::Any },
    { std::string(), TripParameters::SourceType::Any },
    { "first", TripParameters::SourceType::First }
};

static const std::unordered_map<std::string, TripParameters::DestinationType> dest_map {
    { "any", TripParameters::DestinationType::Any },
    { std::string(), TripParameters::DestinationType::Any },
    { "last", TripParameters::DestinationType::Last }
};

#endif //OSRM_NB_TRIPPARAMETER_H
