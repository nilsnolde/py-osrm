Parameters
==========
.. important::
  For a primer on what each parameter does, please refer to the `OSRM documentation <https://project-osrm.org/docs/v5.24.0/api/#>`_.

Keyword Arguments
-----------------
py_osrm's main routing functions accept keyword arguments.

**Kwarg Example**:

.. code-block:: python
  :emphasize-lines: 4-10

  import py_osrm

  match_params = py_osrm.MatchParameters(
    coordinates = three_test_coordinates,
    timestamps = [1424684612, 1424684616, 1424684620],
    radiuses = [4.07, 4.07, 4.07],
    steps = True,
    annotations = ["speed"],
    overview = "false",
    geometries = "geojson"
  )


.. _baseparameters:

Base Parameters
---------------
.. note::
  py_osrm's parameters generally share a parent class ``BaseParameters``.

  This is applicable to:
  :ref:`routeparameters`,
  :ref:`matchparameters`,
  :ref:`nearestparameters`,
  :ref:`tableparameters`,
  :ref:`tripparameters`

.. list-table:: BaseParameters' Attributes
  :widths: 50 150
  :header-rows: 1

  * - Parameter
    - Description
  * - ``coordinates``
    - ``Array`` of ``Float`` ``Pairs``
  * - ``hints``
    - *Currently not supported*
  * - ``radiuses``
    - ``Array`` of ``Float``
  * - ``bearings``
    - ``Array`` of ``Int`` ``Pairs``
  * - ``approaches``
    - *Currently not supported*
  * - ``exclude``
    - ``Array`` of ``(class to avoid)``
  * - ``format``
    - ``"json"`` (default)
  * - ``generate_hints``
    - ``Bool``
  * - ``skip_waypoints``
    - ``Bool``
  * - ``snapping``
    - ``"default"`` (default), ``"any"``

.. list-table:: BaseParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``IsValid()``
    - Runs a basic validation check on input parameter values, returning a Boolean ``True`` if valid, ``False`` if invalid


.. _routeparameters:

Route Parameters
----------------
.. note::
  This class is a derived class of :ref:`baseparameters`

.. code-block:: python

  import py_osrm

  # Declare Parameters
  route_params = py_osrm.RouteParameters(
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],
    steps = True,
    number_of_alternatives = 3,
    annotations = ["speed"],
    geometries = "polyline",
    overview = "simplified",
    continue_straight = False,
    waypoints = [0, 1],
    radiuses = [4.07, 4.07],
    bearings = [(200, 180), (250, 180)],
    # approaches = ["unrestricted", "unrestricted"],
    generate_hints = False,
    exclude = ["motorway"],
    snapping = "any"
  )
  # Assign an Attribute Directly
  route_params.steps = False

  # Print out Validity Status
  print("Valid:", route_params.IsValid())

.. list-table:: RouteParameters' Attributes
   :widths: 50 150
   :header-rows: 1

   * - Parameter
     - Description
   * - ``steps``
     - ``Bool``
   * - ``number_of_alternatives``
     - ``Int``
   * - ``annotations``
     - ``Array`` of ``"none"`` (default), ``"duration"``, ``"nodes"``, ``"distance"``, ``"weight"``, ``"datasources"``, ``"speed"``, ``"all"``
   * - ``geometries``
     - ``"polyline"`` (default), ``"polyline6"``, ``"geojson"``
   * - ``overview``
     - ``"simplified"`` (default), ``"full"``, ``"false"``
   * - ``continue_straight``
     - ``Bool``
   * - ``waypoints``
     - ``Array`` of ``Int``
   * - ``<Inherited Attributes>``
     - Attributes from :ref:`baseparameters`

.. list-table:: RouteParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``<Inherited Functions>``
    - Functions from :ref:`baseparameters`


.. _matchparameters:

Match Parameters
----------------
.. note::
  This class is a derived class of :ref:`routeparameters`

.. code-block:: python

  import py_osrm

  # Declare Parameters
  match_params = py_osrm.MatchParameters(
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077), (7.41862, 43.73216)],
    timestamps = [1424684612, 1424684616, 1424684620],
    gaps = "split",
    tidy = True
  )
  # Assign an Attribute Directly
  match_params.steps = False

  # Print out Validity Status
  print("Valid:", match_params.IsValid())

.. list-table:: MatchParameters' Attributes
   :widths: 50 150
   :header-rows: 1

   * - Parameter
     - Description
   * - ``timestamps``
     - ``Unsigned Int``
   * - ``gaps``
     - ``"split"`` (Default), ``"ignore"``
   * - ``tidy``
     - ``Bool``
   * - ``<Inherited Attributes>``
     - Attributes from :ref:`routeparameters`
   * - ``<Inherited Attributes>``
     - Attributes from :ref:`baseparameters`

.. list-table:: MatchParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``<Inherited Functions>``
    - Functions from :ref:`routeparameters`
  * - ``<Inherited Functions>``
    - Functions from :ref:`baseparameters`

.. _nearestparameters:

Nearest Parameters
------------------
.. note::
  This class is a derived class of :ref:`baseparameters`

.. code-block:: python

  import py_osrm

  # Declare Parameters
  nearest_params = py_osrm.NearestParameters(
    coordinates = [(7.41337, 43.72956)],
    exclude = ["motorway"]
  )
  # Assign an Attribute Directly
  nearest_params.skip_waypoints = False

  # Print out Validity Status
  print("Valid:", nearest_params.IsValid())

.. list-table:: NearestParameters' Attributes
   :widths: 50 150
   :header-rows: 1

   * - Parameter
     - Description
   * - ``<Inherited Attributes>``
     - Attributes from :ref:`baseparameters`

.. list-table:: NearestParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``<Inherited Functions>``
    - Functions from :ref:`baseparameters`


.. _tableparameters:

Table Parameters
------------------
.. note::
  This class is a derived class of :ref:`baseparameters`

.. code-block:: python

  import py_osrm

  # Declare Parameters
  table_params = py_osrm.TableParameters(
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],
    sources = [0],
    destinations = [1],
    annotations = ["duration"],
    fallback_speed = 1,
    fallback_coordinate_type = "input",
    scale_factor = 0.9
  )
  # Assign an Attribute Directly
  table_params.skip_waypoints = False

  # Print out Validity Status
  print("Valid:", table_params.IsValid())

.. list-table:: TableParameters' Attributes
  :widths: 50 150
  :header-rows: 1

  * - Parameter
    - Description
  * - ``sources``
    - ``Array`` of ``Int``
  * - ``destinations``
    - ``Array`` of ``Int``
  * - ``annotations``
    - ``Array`` of ``"none"`` (Default), ``"duration"``, ``"distance"``, ``"all"``
  * - ``fallback_speed``
    - ``Float``
  * - ``fallback_coordinate_type``
    - ``"input"`` (Default), ``"snapped"``
  * - ``scale_factor``
    - ``Float``
  * - ``<Inherited Attributes>``
    - Attributes from :ref:`baseparameters`

.. list-table:: TableParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``<Inherited Functions>``
    - Functions from :ref:`baseparameters`


.. _tileparameters:

Tile Parameters
------------------
.. code-block:: python

  import py_osrm

  # Declare Parameters
  tile_params = py_osrm.TileParameters([17059, 11948, 15])
  tile_params = py_osrm.TileParameters(
    x = 17059,
    y = 11948,
    z = 15
  )
  # Assign an Attribute Directly
  tile_params.x = 17050

  # Print out Validity Status
  print("Valid:", tile_params.IsValid())

.. list-table:: TileParameters' Attributes
  :widths: 50 150
  :header-rows: 1

  * - Parameter
    - Description
  * - ``x``
    - ``Unsigned Int``
  * - ``y``
    - ``Unsigned Int``
  * - ``z``
    - ``Unsigned Int``

.. list-table:: TileParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``IsValid()``
    - Runs a basic validation check on input parameter values, returning a Boolean ``True`` if valid, ``False`` if invalid


.. _tripparameters:

Trip Parameters
------------------
.. note::
  This class is a derived class of :ref:`routeparameters`

.. code-block:: python

  import py_osrm

  # Declare Parameters
  trip_params = py_osrm.TripParameters(
    coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)],
    source = "any",
    destination = "last",
    roundtrip = False
  )
  # Assign an Attribute Directly
  trip_params.overview = "false" 

  # Print out Validity Status
  print("Valid:", trip_params.IsValid())

.. list-table:: TripParameters' Attributes
  :widths: 50 150
  :header-rows: 1

  * - Parameter
    - Description
  * - ``source``
    - ``"any"`` (Default), ``"first"``
  * - ``destination``
    - ``"any"`` (Default), ``"last"``
  * - ``roundtrip``
    - ``Bool``
  * - ``<Inherited Attributes>``
    - Attributes from :ref:`routeparameters`
  * - ``<Inherited Attributes>``
    - Attributes from :ref:`baseparameters`

.. list-table:: TripParameters' Functions
  :widths: 50 150
  :header-rows: 1

  * - Function
    - Description
  * - ``<Inherited Functions>``
    - Functions from :ref:`routeparameters`
  * - ``<Inherited Functions>``
    - Functions from :ref:`baseparameters`
