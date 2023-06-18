#include "osrm/status.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

void init_Status(nb::module_& m) {
    using osrm::engine::Status;

    nb::enum_<Status>(m, "Status")
        .value("Ok", Status::Ok)
        .value("Error", Status::Error)
        .export_values();
}
