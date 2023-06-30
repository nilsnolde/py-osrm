#ifndef OSRM_NB_JSONCONTAINER_H
#define OSRM_NB_JSONCONTAINER_H

#include "util/json_container.hpp"

#include <nanobind/nanobind.h>

#include <string>

void init_JSONContainer(nanobind::module_& m);

namespace json = osrm::util::json;
using JSONValue = mapbox::util::variant<json::String,
                                        json::Number,
                                        mapbox::util::recursive_wrapper<json::Object>,
                                        mapbox::util::recursive_wrapper<json::Array>,
                                        json::True,
                                        json::False,
                                        json::Null>;
//Custom Type Casters
namespace nanobind::detail {

template <> struct type_caster<JSONValue> : type_caster_base<JSONValue> {
    template <typename T> using Caster = make_caster<detail::intrinsic_t<T>>;

    template <typename T>
    static handle from_cpp(T&& val, rv_policy policy, cleanup_list* cleanup) noexcept {
        return mapbox::util::apply_visitor([&](auto &&v) {
            return Caster<decltype(v)>::from_cpp(std::forward<decltype(v)>(v), policy, cleanup);
        }, std::forward<T>(val));
    }
};

template <> struct type_caster<json::String> : type_caster_base<json::String> {
    static handle from_cpp(const json::String& val, rv_policy, cleanup_list*) noexcept {
        return PyUnicode_FromStringAndSize(val.value.c_str(), val.value.size());
    }
};
template <> struct type_caster<json::Number> : type_caster_base<json::Number> {
    static handle from_cpp(const json::Number& val, rv_policy, cleanup_list*) noexcept {
        return PyFloat_FromDouble((double)val.value);
    }
};

template <> struct type_caster<json::True> : type_caster_base<json::True> {
    static handle from_cpp(const json::True&, rv_policy, cleanup_list*) noexcept {
        return handle(Py_True).inc_ref();
    }
};
template <> struct type_caster<json::False> : type_caster_base<json::False> {
    static handle from_cpp(const json::False&, rv_policy, cleanup_list*) noexcept {
        return handle(Py_False).inc_ref();
    }
};
template <> struct type_caster<json::Null> : type_caster_base<json::Null> {
    static handle from_cpp(const json::Null&, rv_policy, cleanup_list*) noexcept {
        return none().release();
    }
};

} //nanobind::detail

struct ValueStringifyVisitor {
    ValueStringifyVisitor(std::string& output) : _output(output) {};
    std::string& _output;

    void operator()(const json::String& str) {
        _output += "'" + str.value + "'";
    }
    void operator()(const json::Number& num) {
        _output += std::to_string(num.value);
    }
    void operator()(const json::True& str) {
        _output += "True";
    }
    void operator()(const json::False&) {
        _output += "False";
    }
    void operator()(const json::Null&) {
        _output += "None";
    }

    void visitarray(const json::Array& arr) {
        _output += "[";
        for(int i = 0; i < arr.values.size(); ++i) {
            if(i != 0) {
                _output += ", ";
            }
            mapbox::util::apply_visitor(*this, arr.values[i]);
        }
        _output += "]";
    }
    void operator()(const mapbox::util::recursive_wrapper<json::Array>& arr) {
        visitarray(arr.get());
    }

    void visitobject(const json::Object& obj) {
        _output += "{";
        bool first = true;
        for(auto itr : obj.values) {
            if(!first) {
                _output += ", ";
            }
            _output += "'" + itr.first + "': ";
            mapbox::util::apply_visitor(*this, itr.second);
            first = false;
        }
        _output += "}";
    }
    void operator()(const mapbox::util::recursive_wrapper<json::Object>& obj) {
        visitobject(obj);
    }
};

#endif //OSRM_NB_JSONCONTAINER_H
