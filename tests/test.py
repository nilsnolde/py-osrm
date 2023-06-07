import py_osrm

config = py_osrm.EngineConfig()
config.use_shared_memory = False
config.algorithm = py_osrm.Algorithm.CoreCH

engine = py_osrm.OSRM(config)
