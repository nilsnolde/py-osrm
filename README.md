# py-osrm
![PR_CI](https://github.com/gis-ops/py-osrm/actions/workflows/pull_request.yml/badge.svg)

### py-osrm is a Python package that binds to [osrm-backend](https://github.com/Project-OSRM/osrm-backend) using [nanobind](https://github.com/wjakob/nanobind).

---

## Supported Platforms
Platform | Arch
---|---
Linux | x86_64
MacOS | x86_64

---

## Installation
py-osrm is supported on **CPython 3.8+**, and can be installed from source via running the following command in the source folder:
```
pip install .
```

## Example
The following example will showcase the process of calculating routes between two coordinates.

First, import the `py_osrm` library, and instantiate an instance of OSRM:
```python
import py_osrm

# Instantiate py_osrm instance
osrm = py_osrm.OSRM("./tests/test_data/ch/monaco.osrm")
```

Then, declare `RouteParameters`, and then pass it into the `py_osrm` instance:
```python
# Declare Route Parameters
route_params = py_osrm.RouteParameters(
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)]
)

# Pass it into the py_osrm instance
res = osrm.Route(route_params)

# Print out result output
print(res["waypoints"])
print(res["routes"])
```

---

## Documentation

