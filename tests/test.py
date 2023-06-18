import py_osrm

config = py_osrm.EngineConfig()
config.use_shared_memory = False
config.algorithm = py_osrm.Algorithm.CH
config.SetStorageConfig("./ch/monaco")

print(config.IsValid())

engine = py_osrm.OSRM(
    storage_config = "./ch/monaco", 
    use_shared_memory = False
)

route_params = py_osrm.RouteParameters(
    steps = True, 
    alternatives = True, 
    annotations = py_osrm.AnnotationsType.None_,
    geometries = py_osrm.GeometriesType.GeoJSON,
    overview = py_osrm.OverviewType.Full,
    continue_straight = True, #py_osrm.OptionalBool(True),
    waypoints = [1],
    coordinates = [(1.0, 2.0)],
    radiuses = [3],
    bearings = [py_osrm.Bearing((3,3))],
    approaches = [py_osrm.Approach.CURB],
    generate_hints = True,
    exclude = [],
    snapping = py_osrm.SnappingType.Default
)

result = py_osrm.Object()

status = engine.Route(route_params, result)
print(status)

for key in result.values:
    print(key, " ", result.values[key])
