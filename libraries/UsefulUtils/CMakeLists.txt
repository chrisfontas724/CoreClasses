cmake_minimum_required(VERSION 3.15)

set(namespace "cxl")
project("UsefulUtils"
    VERSION 0.9.1
    DESCRIPTION "Useful Utils"
)

# Check to see if we are in the top level cmake file or not. The top level call
# to "project()" sets CMAKE_PROJECT_NAME which persists across the levels but
# PROJECT_NAME can be changed.
if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/bounding_box.cpp
        src/debug_print.cpp
        src/dispatch_queue.cpp 
        src/easylogging++.cpp
        src/halton_sampler.cpp
        src/hasher.cpp
        src/transform.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# without it public headers won't get installed
set(public_headers
    include/bounding_box.hpp
    include/debug_print.hpp
    include/dispatch_queue.hpp
    include/easylogging++.h 
    include/factory.hpp
    include/hasher.hpp 
    include/interpolation.hpp
    include/logging.hpp 
    include/rtti.hpp 
    include/service.hpp 
    include/string_utils.hpp
    include/transform.hpp
    include/types.hpp
)

# Find GLM
find_package(glm REQUIRED)
message(STATUS "Version1: GLM included at ${GLM_INCLUDE_DIRS}")
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

target_link_libraries(${PROJECT_NAME} glm)

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#message(STATUS "CMake module path: ${CMAKE_MODULE_PATH}")
include(Installing)