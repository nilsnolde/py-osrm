OSRM
====
OSRM
----
.. important::
  OSRM responses are in JSON format. 
  
  For information on the format of the JSON response for each function, please refer to the `OSRM documentation <https://project-osrm.org/docs/v5.24.0/api/#result-objects>`_.

.. code-block:: python
   :caption: Instantiating OSRM

   import py_osrm

   # Instatiate OSRM by passing in Storage File Path
   osrm = py_osrm.OSRM(".tests/test_data/ch/monaco.osrm")
   # Or passing in EngineConfig Kwargs
   osrm = py_osrm.OSRM(
     algorithm = "CH",
     storage_config = ".tests/test_data/ch/monaco.osrm",
     max_locations_trip = 3,
     max_locations_viaroute = 3,
     max_locations_distance_table = 3,
     max_locations_map_matching = 3,
     max_results_nearest = 1,
     max_alternatives = 1,
     default_radius = "unlimited"
   )


.. list-table:: Instantiating OSRM
  :widths: 75 125
  :header-rows: 1

  * - Parameter
    - Description
  * - ``(String to Storage Path)``
    - ``String``
  * - ``<Engine Config Keyword Arguments>``
    - Attributes from :ref:`engineconfig`


.. code-block:: python
   :caption: Routing Example

   # Declare Route Coordinates
   route_params = py_osrm.RouteParameters(
      coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)]
   )

   # Pass it into the py_osrm instance
   res = osrm.Route(route_params)

   # Print out the Distance and Duration of the first Route
   print("Distance:", res["routes"][0]["distance"])
   print("Duration:", res["routes"][0]["duration"])


.. list-table:: OSRM Functions
  :widths: 20 50 115 15
  :header-rows: 1

  * - Function
    - Input
    - Description
    - Result
  * - ``Match``
    - :ref:`matchparameters`
    - *Map matching matches/snaps given GPS points to the road network in the most plausible way.*
    - `JSON <https://project-osrm.org/docs/v5.24.0/api/#match-service>`_
  * - ``Nearest``
    - :ref:`nearestparameters`
    - *Snaps a coordinate to the street network and returns the nearest matches.*
    - `JSON <https://project-osrm.org/docs/v5.24.0/api/#nearest-service>`_
  * - ``Route``
    - :ref:`routeparameters`
    - *Finds the fastest route between coordinates in the supplied order.*
    - `JSON <https://project-osrm.org/docs/v5.24.0/api/#route-service>`_
  * - ``Table``
    - :ref:`tableparameters`
    - *Computes the duration of the fastest route between all pairs of supplied coordinates.*
    - `JSON <https://project-osrm.org/docs/v5.24.0/api/#table-service>`_
  * - ``Tile``
    - :ref:`tileparameters`
    - *This service generates Mapbox Vector Tiles that can be viewed with a vector-tile capable slippy-map viewer.*
    - `JSON <https://project-osrm.org/docs/v5.24.0/api/#tile-service>`_
  * - ``Trip``
    - :ref:`tripparameters`
    - *The trip plugin solves the Traveling Salesman Problem using a greedy heuristic (farthest-insertion algorithm).*
    - `JSON <https://project-osrm.org/docs/v5.24.0/api/#trip-service>`_


.. _engineconfig:

EngineConfig
-------------
.. list-table:: EngineConfig Keyword Arguments
  :widths: 50 150
  :header-rows: 1

  * - Parameter
    - Description
  * - ``storage_config``
    - ``String``
  * - ``max_locations_trip``
    - ``Int``
  * - ``max_locations_viaroute``
    - ``Int``
  * - ``max_locations_distance_table``
    - ``Int``
  * - ``max_locations_map_matching``
    - ``Int``
  * - ``max_radius_map_matching``
    - ``Float``
  * - ``max_results_nearest``
    - ``Int``
  * - ``default_radius``
    - ``Float``, ``"unlimited"``, ``"UNLIMITED"``
  * - ``max_alternatives``
    - ``Int``
  * - ``use_shared_memory``
    - ``Bool``
  * - ``memory_file``
    - ``String``
  * - ``use_mmap``
    - ``Bool``
  * - ``algorithm``
    - ``CH`` (Default), ``CoreCH``, ``MLD``
  * - ``verbosity``
    - ``String``
  * - ``dataset_name``
    - ``String``
