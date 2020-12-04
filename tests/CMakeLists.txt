set(TEST_SOURCE
   ${TEST_SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/dispatch_unittest.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../dispatch_queue.cpp
   PARENT_SCOPE
)

include_directories("${gtest_SOURCE_DIR}/include")

