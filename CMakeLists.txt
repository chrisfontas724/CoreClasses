# Make sure we have the right version of CMake.
cmake_minimum_required (VERSION 3.7)


# C++ Compiler Settings.
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "-std=gnu++17")


add_library (core
    logging/easylogging++.cc
    threading/dispatch_queue.cpp
    utils/hasher.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# To allow logging in test
set(TEST_SOURCE
   ${TEST_SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/logging/easylogging++.cc
   PARENT_SCOPE
)