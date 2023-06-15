# Copyright 2019 Chris Fontas. All rights reserved.
# Use of this source code is governed by the license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.15)

project("Useful_Utils"
    VERSION 0.9.1
    DESCRIPTION "A project to test out useful utils"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libraries)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE UsefulUtils)