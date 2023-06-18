#include "util/json_container.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;

void init_JSONContainer(nb::module_& m) {
    namespace json = osrm::util::json;

    nb::class_<json::Object>(m, "Object")
        .def(nb::init<>())
        .def_rw("values", &json::Object::values);

    nb::class_<json::Array>(m, "Array")
        .def(nb::init<>())
        .def_rw("values", &json::Array::values);

    nb::class_<json::String>(m, "String")
        .def(nb::init<>())
        .def(nb::init<std::string>())
        .def_rw("value", &json::String::value);

    nb::class_<json::Number>(m, "Number")
        .def(nb::init<>())
        .def(nb::init<double>())
        .def_rw("value", &json::Number::value);

    nb::class_<json::True>(m, "True")
        .def(nb::init<>());
    nb::class_<json::False>(m, "False")
        .def(nb::init<>());
    nb::class_<json::Null>(m, "Null")
        .def(nb::init<>());

    using Value = mapbox::util::variant<json::String,
                                        json::Number,
                                        mapbox::util::recursive_wrapper<json::Object>,
                                        mapbox::util::recursive_wrapper<json::Array>,
                                        json::True,
                                        json::False,
                                        json::Null>;
    nb::class_<Value>(m, "Value")
        .def(nb::init<>())
        .def("valid", &Value::valid);
}
