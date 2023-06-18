#include "util/coordinate.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/pair.h>

namespace nb = nanobind;
using namespace nb::literals;

void init_Coordinate(nb::module_& m) {    
    namespace tag = osrm::util::tag;
    using FixedLatitude = osrm::Alias<int32_t, tag::latitude>;
    using FixedLongitude = osrm::Alias<int32_t, tag::longitude>;
    using FloatLatitude = osrm::Alias<double, tag::latitude>;
    using FloatLongitude = osrm::Alias<double, tag::longitude>;
    using UnsafeFloatLatitude = osrm::Alias<double, tag::unsafelatitude>;
    using UnsafeFloatLongitude = osrm::Alias<double, tag::unsafelongitude>;

    using osrm::util::Coordinate;
    using osrm::util::FloatCoordinate;

    nb::class_<FixedLatitude>(m, "FixedLatitude")
        .def(nb::init<>())
        .def(nb::init<int32_t>());
    nb::class_<FloatLatitude>(m, "FloatLatitude")
        .def(nb::init<>())
        .def(nb::init<double>());
    nb::class_<UnsafeFloatLatitude>(m, "UnsafeFloatLatitude")
        .def(nb::init<>())
        .def(nb::init<double>())
        .def(nb::init_implicit<double>());

    nb::class_<FixedLongitude>(m, "FixedLongitude")
        .def(nb::init<>())
        .def(nb::init<int32_t>());
    nb::class_<FloatLongitude>(m, "FloatLongitude")
        .def(nb::init<>())
        .def(nb::init<double>());
    nb::class_<UnsafeFloatLongitude>(m, "UnsafeFloatLongitude")
        .def(nb::init<>())
        .def(nb::init<double>())
        .def(nb::init_implicit<double>());

    nb::class_<FloatCoordinate>(m, "FloatCoordinate")
        .def(nb::init<>())
        .def(nb::init<const Coordinate>(), "other"_a)
        .def(nb::init<const FixedLongitude, const FixedLatitude>(),
            "lon"_a, "lat"_a)
        .def(nb::init<const FloatLongitude, const FloatLatitude>(),
            "lon"_a, "lat"_a)
        .def_rw("lon", &FloatCoordinate::lon)
        .def_rw("lat", &FloatCoordinate::lat)
        .def("IsValid", &FloatCoordinate::IsValid)
        .def(nb::self == nb::self)
        .def(nb::self != nb::self);

    nb::class_<Coordinate>(m, "Coordinate")
        .def(nb::init<>())
        .def(nb::init<const Coordinate&>(),"coordinate"_a)
        .def(nb::init<const FloatCoordinate&>(), "other"_a)
        .def(nb::init<const FixedLongitude, const FixedLatitude>(),
            "lon"_a, "lat"_a)
        .def(nb::init<const FloatLongitude, const FloatLatitude>(),
            "lon"_a, "lat"_a)
        .def(nb::init<const UnsafeFloatLongitude, const UnsafeFloatLatitude>(),
            "lon"_a, "lat"_a)
        .def("__init__", [](Coordinate* t, std::pair<double, double> coords) {
            const UnsafeFloatLongitude lon_ = UnsafeFloatLongitude{coords.first};
            const UnsafeFloatLatitude lat_ = UnsafeFloatLatitude{coords.second};

            new (t) Coordinate(lon_, lat_);
         })
        .def_rw("lon", &Coordinate::lon)
        .def_rw("lat", &Coordinate::lat)
        .def("IsValid", &Coordinate::IsValid)
        .def(nb::self == nb::self)
        .def(nb::self != nb::self);

    nb::implicitly_convertible<std::pair<double, double>, Coordinate>();
}