# py-osrm
**py-osrm is a Python package that binds to [osrm-backend](https://github.com/Project-OSRM/osrm-backend) using [nanobind](https://github.com/wjakob/nanobind).
The original repo seems to be a bit stale and does not compile on linux. So I tried my best to get it working again.**

## ToDos
- [x] make it compile in a docker container
- [x] provide a docker file
- [ ] update the readme with proper examples
- [ ] switch to nanobind 2
- [ ] skip the json part an provide a numpy adapter
- [ ] use a minimum of dirty hacks

---

## Supported Platforms
Platform | Arch | Compilation
---|--- | ---
Linux | x86_64 | tested
MacOS | x86_64 | untested
Windows | x86_64 | untested
---

## Installation
py-osrm is supported on **CPython 3.8+ (tested on 3.11)**, and can be installed from source via running the following command in the source folder:
```
pip install .
```

## Example
The following example will showcase the process of calculating routes between two coordinates.

First, import the `osrm` library, and instantiate an instance of OSRM:
```python
import osrm

# Instantiate py_osrm instance
py_osrm = osrm.OSRM("./tests/test_data/ch/monaco.osrm")
```

Then, declare `RouteParameters`, and then pass it into the `py_osrm` instance:
```python
# Declare Route Parameters
route_params = osrm.RouteParameters(
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)]
)

# Pass it into the py_osrm instance
res = py_osrm.Route(route_params)

# Print out result output
print(res["waypoints"])
print(res["routes"])
```

---

## Documentation
[Documentation Page](https://gis-ops.github.io/py-osrm/)
