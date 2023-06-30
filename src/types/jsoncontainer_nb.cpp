#include "types/jsoncontainer_nb.h"

#include "util/json_container.hpp"

#include <mapbox/variant.hpp>

#include <nanobind/nanobind.h>
#include <nanobind/make_iterator.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
namespace json = osrm::util::json;

void init_JSONContainer(nb::module_& m) {
    nb::class_<json::Object>(m, "Object")
        .def(nb::init<>())
        .def("__len__", [](const json::Object& obj) {
            return obj.values.size();
        })
        .def("__bool__", [](const json::Object& obj) {
            return obj.values.empty();
        })
        .def("__repr__", [](json::Object& obj) {
            std::string output = "";
            ValueStringifyVisitor visitor(output);
            visitor.visitobject(obj);

            return output;
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
        .def("__repr__", [](const json::Array& arr) {
            std::string output = "";
            ValueStringifyVisitor visitor(output);
            visitor.visitarray(arr);

            return output;
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
