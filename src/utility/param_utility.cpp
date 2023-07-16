#include "utility/param_utility.h"

#include "engine/approach.hpp"
#include "engine/api/base_parameters.hpp"
#include "engine/api/match_parameters.hpp"
#include "engine/api/route_parameters.hpp"
#include "engine/api/table_parameters.hpp"
#include "engine/api/trip_parameters.hpp"

#include <boost/optional.hpp>

#include <unordered_map>
#include <vector>

using osrm::engine::Approach;
using osrm::engine::api::BaseParameters;
using osrm::engine::api::MatchParameters;
using osrm::engine::api::RouteParameters;
using osrm::engine::api::TableParameters;
using osrm::engine::api::TripParameters;

namespace osrm_nb_util {

std::vector<boost::optional<osrm::engine::Approach>> get_approach(const std::vector<std::string*>& strs) {
    std::vector<boost::optional<osrm::engine::Approach>> res(strs.size());
    
    if(strs.empty()) {
        return res;
    }

    for(int i = 0; i < strs.size(); ++i) {
        if(strs[i] == nullptr) {
            continue;
        }

        if(*strs[i] == "curb") {
            res[i] = Approach::CURB;
        }
        else if(*strs[i] == "any") {
            res[i] = Approach::UNRESTRICTED;
        }
        else {
            throw std::invalid_argument("Invalid Argument for Approach: " + *strs[i]);
        }
    }
    
    return res;
}

BaseParameters::SnappingType get_snapping_type(const std::string& str) {
    if(str.empty() || str == "default") {
        return BaseParameters::SnappingType::Default;
    }
    else if(str == "any") {
        return BaseParameters::SnappingType::Any;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Snapping Type: " + str);
    }
}

BaseParameters::OutputFormatType get_format_type(const std::string& str) {
    if(str == "json") {
        return BaseParameters::OutputFormatType::JSON;
    }
    else if(str == "flatbuffers") {
        return BaseParameters::OutputFormatType::FLATBUFFERS;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Format Type: " + str);
    }
}

RouteParameters::AnnotationsType get_routeannotations_type(const std::vector<std::string>& strs) {
    if(strs.empty()) {
        return RouteParameters::AnnotationsType::None;
    }

    RouteParameters::AnnotationsType res = RouteParameters::AnnotationsType::None;

    const std::unordered_map<std::string, RouteParameters::AnnotationsType> annotations_map {
        { "none", RouteParameters::AnnotationsType::None },
        { "duration", RouteParameters::AnnotationsType::Duration },
        { "nodes", RouteParameters::AnnotationsType::Nodes },
        { "distance", RouteParameters::AnnotationsType::Distance },
        { "weight", RouteParameters::AnnotationsType::Weight },
        { "datasources", RouteParameters::AnnotationsType::Datasources },
        { "speed", RouteParameters::AnnotationsType::Speed },
        { "all", RouteParameters::AnnotationsType::All }
    };

    for(int i = 0; i < strs.size(); ++i) {
        auto itr = annotations_map.find(strs[i]);

        if(itr == annotations_map.end()) {
            throw std::invalid_argument("Invalid Argument for Annotations Type: " + strs[i]);
        }
        
        res = res | itr->second;
    }
    
    return res;
}

RouteParameters::GeometriesType get_geometries_type(const std::string& str) {
    if(str.empty() || str == "polyline") {
        return RouteParameters::GeometriesType::Polyline;
    }
    else if(str == "polyline6") {
        return RouteParameters::GeometriesType::Polyline6;
    }
    else if(str == "geojson") {
        return RouteParameters::GeometriesType::GeoJSON;        
    }
    else {
        throw std::invalid_argument("Invalid Argument for Geometries Type: " + str);
    }  
}

RouteParameters::OverviewType get_overview_type(const std::string& str) {
    if(str.empty() || str == "simplified") {
        return RouteParameters::OverviewType::Simplified;
    }
    else if(str == "full") {
        return RouteParameters::OverviewType::Full;
    }
    else if(str == "false") {
        return RouteParameters::OverviewType::False;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Overview Type: " + str);
    }  
}

MatchParameters::GapsType get_gaps_type(const std::string& str = "split") {
    if(str.empty() || str == "split") {
        return MatchParameters::GapsType::Split;
    }
    else if(str == "ignore") {
        return MatchParameters::GapsType::Ignore;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Gaps Type: " + str);
    }
}

TableParameters::FallbackCoordinateType get_fallbackcoordinate_type(const std::string& str) {
    if(str.empty() || str == "input") {
        return TableParameters::FallbackCoordinateType::Input;
    }
    else if(str == "ignore") {
        return TableParameters::FallbackCoordinateType::Snapped;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Fallback Coordinate Type: " + str);
    }
}

TableParameters::AnnotationsType get_tableannotations_type(const std::vector<std::string>& strs) {
    if(strs.empty()) {
        return TableParameters::AnnotationsType::Duration;
    }

    TableParameters::AnnotationsType res = TableParameters::AnnotationsType::None;

    const std::unordered_map<std::string, TableParameters::AnnotationsType> annotations_map {
        { "none", TableParameters::AnnotationsType::None },
        { "duration", TableParameters::AnnotationsType::Duration },
        { "distance", TableParameters::AnnotationsType::Distance },
        { "all", TableParameters::AnnotationsType::All }
    };

    for(int i = 0; i < strs.size(); ++i) {
        auto itr = annotations_map.find(strs[i]);

        if(itr == annotations_map.end()) {
            throw std::invalid_argument("Invalid Argument for Annotations Type: " + strs[i]);
        }
        
        res = res | itr->second;
    }
    
    return res;
}

TripParameters::SourceType get_tripsource_type(const std::string& str) {
    if(str.empty() || str == "any") {
        return TripParameters::SourceType::Any;
    }
    else if(str == "first") {
        return TripParameters::SourceType::First;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Trip Source Type: " + str);
    }
}

TripParameters::DestinationType get_tripdestination_type(const std::string& str) {
    if(str.empty() || str == "any") {
        return TripParameters::DestinationType::Any;
    }
    else if(str == "last") {
        return TripParameters::DestinationType::Last;
    }
    else {
        throw std::invalid_argument("Invalid Argument for Trip Source Type: " + str);
    }
}

} //namespace osrm_nb_util
