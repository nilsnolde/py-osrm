import py_osrm

config = py_osrm.EngineConfig()
config.use_shared_memory = False
config.algorithm = py_osrm.Algorithm.CH
config.SetStorageConfig("./test_data/ch/monaco")

print(config.IsValid())

engine = py_osrm.OSRM(
    storage_config = "./test_data/ch/monaco", 
    use_shared_memory = False
)

route_params = py_osrm.RouteParameters(
    steps = True, 
    alternatives = True, 
    annotations = py_osrm.RouteAnnotationsType.None_,
    geometries = py_osrm.RouteGeometriesType.GeoJSON,
    overview = py_osrm.RouteOverviewType.Full,
    continue_straight = True, #py_osrm.OptionalBool(True),
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)]
)
result = py_osrm.Object()

status = engine.Route(route_params, result)
print(status)

print(result["code"])
print(result["message"])

for route in result["routes"]:
    for obj in route:
        print(obj)
