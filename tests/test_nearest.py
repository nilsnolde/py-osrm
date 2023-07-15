import py_osrm
import constants

mld_data_path = constants.mld_data_path
two_test_coordinates = constants.two_test_coordinates

class TestNearest:
    osrm = py_osrm.OSRM(
        storage_config = mld_data_path, 
        algorithm = "MLD",
        use_shared_memory = False
    )

    def test_nearest(self):
        nearest_params = py_osrm.NearestParameters(
            coordinates = [two_test_coordinates[0]],
            exclude = ["motorway"]
        )
        res = self.osrm.Nearest(nearest_params)
        assert(len(res["waypoints"]) == 1)
