#include "util/json_container.hpp"

#include <mapbox/variant.hpp>

#include <nanobind/nanobind.h>
#include <nanobind/make_iterator.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
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

void init_JSONContainer(nb::module_& m) {
    nb::class_<json::Object>(m, "Object")
        .def(nb::init<>())
        .def("__len__", [](const json::Object& obj) {
            return obj.values.size();
        })
        .def("__bool__", [](const json::Object& obj) {
            return obj.values.empty();
        })
        .def("__getitem__", [](json::Object& obj, const std::string& key) {
            return obj.values[key];
        })
        .def("__iter__", [](const json::Object& obj) {
            return nb::make_iterator(nb::type<json::Value>(), "iterator",
                                    obj.values.begin(), obj.values.end());
        }, nb::keep_alive<0, 1>());

    nb::class_<json::Array>(m, "Array")
        .def(nb::init<>())
        .def("__len__", [](const json::Array& arr) {
            return arr.values.size();
        })
        .def("__bool__", [](const json::Array& arr) {
            return arr.values.empty();
        })
        .def("__iter__", [](const json::Array& arr) {
            return nb::make_iterator(nb::type<json::Value>(), "iterator",
                                    arr.values.begin(), arr.values.end());
        }, nb::keep_alive<0, 1>());

    nb::class_<json::String>(m, "String")
        .def(nb::init<std::string>());
    nb::class_<json::Number>(m, "Number")
        .def(nb::init<double>());

    nb::class_<json::True>(m, "True")
        .def(nb::init<>());
    nb::class_<json::False>(m, "False")
        .def(nb::init<>());
    nb::class_<json::Null>(m, "Null")
        .def(nb::init<>());
}
