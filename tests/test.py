import py_osrm

config = py_osrm.EngineConfig()
config.use_shared_memory = False
config.algorithm = py_osrm.Algorithm.CH
config.SetStorageConfig("./ch/monaco")

print(config.IsValid())

engine = py_osrm.OSRM(storage_config = "./ch/monaco", use_shared_memory = False)

route_params = py_osrm.RouteParameters()
engine.Route(route_params)
