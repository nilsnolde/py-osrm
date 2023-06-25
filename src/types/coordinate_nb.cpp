#include "util/coordinate.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/pair.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_Coordinate(nb::module_& m) {    
    namespace tag = osrm::util::tag;
    using FloatLongitude = osrm::Alias<double, tag::longitude>;
    using FloatLatitude = osrm::Alias<double, tag::latitude>;
    
    using osrm::util::Coordinate;
    using osrm::util::FloatCoordinate;

    nb::class_<FloatCoordinate>(m, "FloatCoordinate")
        .def(nb::init<>())
        .def(nb::init<const Coordinate>(), "other"_a)
        .def("__init__", [](FloatCoordinate* t, std::pair<double, double> coords) {
            const FloatLongitude lon_ = FloatLongitude{coords.first};
            const FloatLatitude lat_ = FloatLatitude{coords.second};

            new (t) FloatCoordinate(lon_, lat_);
         })
        .def_rw("lon", &FloatCoordinate::lon)
        .def_rw("lat", &FloatCoordinate::lat)
        .def("IsValid", &FloatCoordinate::IsValid)
        .def(nb::self == nb::self)
        .def(nb::self != nb::self);
    nb::implicitly_convertible<std::pair<double, double>, FloatCoordinate>();

    nb::class_<Coordinate>(m, "Coordinate")
        .def(nb::init<>())
        .def(nb::init<const Coordinate&>(),"coordinate"_a)
        .def(nb::init<const FloatCoordinate&>(), "other"_a)
        .def("__init__", [](Coordinate* t, std::pair<double, double> coords) {
            const FloatLongitude lon_ = FloatLongitude{coords.first};
            const FloatLatitude lat_ = FloatLatitude{coords.second};

            new (t) Coordinate(lon_, lat_);
         })
        .def_rw("lon", &Coordinate::lon)
        .def_rw("lat", &Coordinate::lat)
        .def("IsValid", &Coordinate::IsValid)
        .def(nb::self == nb::self)
        .def(nb::self != nb::self);
    nb::implicitly_convertible<std::pair<double, double>, Coordinate>();
}
