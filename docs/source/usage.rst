Usage
=====

.. _installation:

Installation
------------
py_osrm can be installed via either pip (recommended) or source.

pip:

.. code-block:: console

   $ pip install py_osrm

source:

.. code-block:: console
   
   $ git clone https://github.com/gis-ops/py-osrm.git
   $ cd py-osrm
   $ pip install .

Example
-------

**Quick Example**:

.. code-block:: python

   import py_osrm

   osrm = py_osrm.OSRM(".tests/test_data/ch/monaco.osrm")

   # Declare Route Coordinates
   route_params = py_osrm.RouteParameters(
      coordinates = [(7.41337, 43.72956), (7.41546, 43.73077)]
   )

   # Pass it into the py_osrm instance
   res = osrm.Route(route_params)

   # Print out the Distance and Duration of the first Route
   print("Distance:", res["routes"][0]["distance"])
   print("Duration:", res["routes"][0]["duration"])
