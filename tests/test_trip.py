import osrm
import constants

data_path = constants.data_path
mld_data_path = constants.mld_data_path
three_test_coordinates = constants.three_test_coordinates
two_test_coordinates = constants.two_test_coordinates

class TestTrip:
    py_osrm = osrm.OSRM(
        storage_config = data_path, 
        use_shared_memory = False
    )

    def test_trip_manylocations(self):
        trip_parameters = osrm.TripParameters(
            coordinates = three_test_coordinates[0:5]
        )
        res = self.py_osrm.Trip(trip_parameters)
        for trip in res["trips"]:
            assert(trip["geometry"])

    def test_trip_invalidargs(self):
        py_osrm = osrm.OSRM()
        trip_parameters = osrm.TripParameters(
            coordinates = two_test_coordinates
        )
        res = py_osrm.Trip(trip_parameters)
        for trip in res["trips"]:
            assert(trip["geometry"])

    # def test_trip_hints(self):
    #     trip_parameters = osrm.TripParameters(
    #         coordinates = two_test_coordinates,
    #         steps = False
    #     )
    #     res = self.py_osrm.Trip(trip_parameters)
    #  
    #     for trip in res["trips"]:
    #         assert(trip["geometry"])
    #     assert(res["waypoints"]["map"])
    #     for h in res["waypoints"]["map"]:
    #         assert(isinstance(h, str))

    def test_trip_geometrycompression(self):
        py_osrm = osrm.OSRM()
        trip_parameters = osrm.TripParameters(
            coordinates = [three_test_coordinates[0], three_test_coordinates[1]]
        )
        res = py_osrm.Trip(trip_parameters)
        for trip in res["trips"]:
            assert(isinstance(trip["geometry"], str))

    def test_trip_nogeometrycompression(self):
        py_osrm = osrm.OSRM()
        trip_parameters = osrm.TripParameters(
            coordinates = two_test_coordinates,
            geometries = "geojson"
        )
        res = py_osrm.Trip(trip_parameters)
        for trip in res["trips"]:
            assert(isinstance(trip["geometry"]["coordinates"], osrm.Array))
    
    def test_trip_speedannotations(self):
        py_osrm = osrm.OSRM()
        trip_parameters = osrm.TripParameters(
            coordinates = two_test_coordinates,
            steps = True,
            annotations = ["speed"],
            overview = "false"
        )
        res = py_osrm.Trip(trip_parameters)
        for trip in res["trips"]:
            assert(trip)
            for l in trip["legs"]:
                assert(len(l["steps"]) > 0
                    and l["annotation"] 
                    and l["annotation"]["speed"])
                assert(not l["annotation"]["weight"] 
                    and not l["annotation"]["datasources"]
                    and not l["annotation"]["duration"] 
                    and not l["annotation"]["distance"] 
                    and not l["annotation"]["nodes"])
                assert(not l["geometry"])

    def test_trip_severalannotations(self):
        trip_params = osrm.TripParameters(
            coordinates = two_test_coordinates,
            steps = True,
            annotations = ["duration", "distance", "nodes"],     
            overview = "false"
        )
        res = self.py_osrm.Trip(trip_params)
        assert(len(res["trips"]) == 1)
        for trip in res["trips"]:
            assert(trip)
            for l in trip["legs"]:
                assert(len(l["steps"]) > 0)
                assert(l["annotation"]
                    and l["annotation"]["distance"] 
                    and l["annotation"]["duration"] 
                    and l["annotation"]["nodes"])
                assert(not l["annotation"]["weight"]
                    and not l["annotation"]["datasources"] 
                    and not l["annotation"]["speed"])
                assert(not l["geometry"])

    def test_trip_options(self):
        trip_params = osrm.TripParameters(
            coordinates = two_test_coordinates,
            steps = True,
            annotations = ["all"],
            overview = "false"        
        )
        res = self.py_osrm.Trip(trip_params)
        assert(len(res["trips"]) == 1)
        for trip in res["trips"]:
            assert(trip)
            for l in trip["legs"]:
                assert(len(l["steps"]) > 0
                       and l["annotation"])
            assert(not trip["geometry"])

    def test_trip_nomotorways(self):
        py_osrm = osrm.OSRM(
            algorithm = "MLD",
            storage_config = mld_data_path,
            use_shared_memory = False
        )
        trip_params = osrm.TripParameters(
            coordinates = two_test_coordinates,
            exclude = ["motorway"]      
        )
        res = py_osrm.Trip(trip_params)
        assert(len(res["waypoints"]) == 2)
        assert(len(res["trips"]) == 1)
