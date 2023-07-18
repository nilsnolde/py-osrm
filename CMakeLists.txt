cmake_minimum_required(VERSION 3.18)

set(PROJECT_NAME "py_osrm")
set(EXT_NAME "osrm_ext")
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT SKBUILD)
  message(WARNING
  "This CMake file is meant to be executed using 'scikit-build-core'.
  Running it directly will almost certainly not produce the desired
  result. If you are a user trying to install this package, use the
  command below, which will install all necessary build dependencies,
  compile the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  ====================================================================="
  )
endif()

find_package(Python 3.7
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule
)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR
)

list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

set(SRCS
  src/osrm_nb.cpp
  src/engineconfig_nb.cpp
  src/utility/osrm_utility.cpp
  src/utility/param_utility.cpp

  src/parameters/baseparameter_nb.cpp
  src/parameters/routeparameter_nb.cpp
  src/parameters/matchparameter_nb.cpp
  src/parameters/nearestparameter_nb.cpp
  src/parameters/tableparameter_nb.cpp
  src/parameters/tileparameter_nb.cpp
  src/parameters/tripparameter_nb.cpp
  
  src/types/optional_nb.cpp
  src/types/coordinate_nb.cpp
  src/types/jsoncontainer_nb.cpp
  src/types/approach_nb.cpp
  src/types/bearing_nb.cpp
)
nanobind_add_module(
  ${EXT_NAME}
  STABLE_ABI
  NB_STATIC
  ${SRCS}
  ${UTIL}
  ${PARAMS}
)

target_include_directories(${EXT_NAME} 
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utility
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parameters
)

include(FetchContent)
FetchContent_Declare(
  libosrm
  GIT_REPOSITORY https://github.com/Project-OSRM/osrm-backend
  GIT_TAG master
)

FetchContent_GetProperties(libosrm)
if(NOT libosrm_POPULATED)
  FetchContent_Populate(libosrm)
  add_subdirectory(
    ${libosrm_SOURCE_DIR}
    ${libosrm_BINARY_DIR}
    EXCLUDE_FROM_ALL
  )
endif()

target_include_directories(${EXT_NAME} 
  PUBLIC
    ${libosrm_SOURCE_DIR}/include
)
target_link_libraries(${EXT_NAME}
  PRIVATE
    osrm
)

install(TARGETS ${EXT_NAME} LIBRARY DESTINATION ${PROJECT_NAME})
