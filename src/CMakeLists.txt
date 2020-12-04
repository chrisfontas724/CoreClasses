# Copyright 2019 Chris Fontas. All rights reserved.
# Use of this source code is governed by the license that can be
# found in the LICENSE file.

set(LIBRARY_NAME core)

set(HEADER_LIST 
    "${Core_SOURCE_DIR}/include/core/dispatch_queue.hpp" 
    "${Core_SOURCE_DIR}/include/core/factory.hpp"
    "${Core_SOURCE_DIR}/include/core/hasher.hpp"
    "${Core_SOURCE_DIR}/include/core/logging.hpp"
    "${Core_SOURCE_DIR}/include/core/rtti.hpp"
    "${Core_SOURCE_DIR}/include/core/service.hpp"
    "${Core_SOURCE_DIR}/include/core/string_utils.hpp"
)

# Make an automatic library - will be static or dynamic based on user setting
add_library(core 
    dispatch_queue.cpp
    easylogging++.cc
    hasher.cpp
    ${HEADER_LIST})

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)
target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

# All users of this library will need at least C++11
target_compile_features(core PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
