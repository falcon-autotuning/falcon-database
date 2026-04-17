find_package(GTest REQUIRED)
include(GoogleTest)

set(DLL_SEARCH_PATHS "${CMAKE_BINARY_DIR}}/tests" "${CMAKE_BINARY_DIR}")
string(REPLACE ";" "\\;" TEST_PATH_ENV "${DLL_SEARCH_PATHS}")
set(TEST_PATH_ENV "${TEST_PATH_ENV};$ENV{PATH}")

# Test utilities
add_library(falcon-db-test-utils STATIC
  test_utils/DatabaseTestFixture.cpp
)

target_link_libraries(falcon-db-test-utils
  PUBLIC
    falcon-database
    GTest::gtest
)

target_include_directories(falcon-db-test-utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/test_utils
)

# Unit tests
add_executable(falcon_db_unit_tests
  unit/test_device_characteristic.cpp
  unit/test_database_operations.cpp
)

target_link_libraries(falcon_db_unit_tests
  PRIVATE
    falcon-database
    falcon-db-test-utils
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME falcon_db_unit_tests COMMAND falcon_db_unit_tests)
if(WIN32)
  set_tests_properties(falcon_db_unit_tests 
    PROPERTIES ENVIRONMENT "PATH=${TEST_PATH_ENV}")
endif()

# Integration tests
add_executable(falcon_db_integration_tests
  integration/test_snapshot_manager.cpp
  integration/test_full_workflow.cpp
  integration/test_cli.cpp
)

target_link_libraries(falcon_db_integration_tests
  PRIVATE
    falcon-database
    falcon-db-test-utils
    GTest::gtest
    GTest::gtest_main
)
add_test(NAME falcon_db_integration_tests COMMAND falcon_db_integration_tests)
if(WIN32)
  set_tests_properties(falcon_db_integration_tests
    PROPERTIES ENVIRONMENT "PATH=${TEST_PATH_ENV}")
endif()
