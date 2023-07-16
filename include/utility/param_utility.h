#ifndef OSRM_NB_PARAM_UTIL_H
#define OSRM_NB_PARAM_UTIL_H

#include "engine/approach.hpp"
#include "engine/api/base_parameters.hpp"
#include "engine/api/match_parameters.hpp"
#include "engine/api/route_parameters.hpp"
#include "engine/api/table_parameters.hpp"
#include "engine/api/trip_parameters.hpp"

#include <vector>

using osrm::engine::Approach;
using osrm::engine::api::BaseParameters;
using osrm::engine::api::MatchParameters;
using osrm::engine::api::RouteParameters;
using osrm::engine::api::TableParameters;
using osrm::engine::api::TripParameters;

namespace osrm_nb_util {

std::vector<boost::optional<osrm::engine::Approach>> get_approach(const std::vector<std::string*>& approach_strs);

BaseParameters::SnappingType get_snapping_type(const std::string& snapping_str);
BaseParameters::OutputFormatType get_format_type(const std::string& format_str);

RouteParameters::AnnotationsType get_routeannotations_type(const std::vector<std::string>& annotation_strs);
RouteParameters::GeometriesType get_geometries_type(const std::string& geometries_str);
RouteParameters::OverviewType get_overview_type(const std::string& overview_str);

MatchParameters::GapsType get_gaps_type(const std::string& gaps_str);

TableParameters::FallbackCoordinateType get_fallbackcoordinate_type(const std::string& fallbackcoord_str);
TableParameters::AnnotationsType get_tableannotations_type(const std::vector<std::string>& strs);

TripParameters::SourceType get_tripsource_type(const std::string& tripsource_str);
TripParameters::DestinationType get_tripdestination_type(const std::string& tripdestination_str);

} //namespace osrm_nb_util

#endif //OSRM_NB_PARAM_UTIL_H
