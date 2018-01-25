cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

set(TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/TestData)
configure_file(TestsConfig.h.in ${CMAKE_CURRENT_SOURCE_DIR}/TestsConfig.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_executable(ip_filter ip_filter.cpp)

add_library(ip_filter_lib lib.cpp lib.h  version.h)

add_executable(test_ip_filter test.cpp lib.h)

set_target_properties(ip_filter ip_filter_lib test_ip_filter PROPERTIES
                      CXX_STANDARD 14
                      CXX_STANDARD_REQUIRED ON)

if(${GCC})
set_target_properties(ip_filter ip_filter_lib test_ip_filter PROPERTIES
                      COMPILE_OPTIONS -Wpedantic -Wall -Wextra
                                        )
elseif(${WIN})
set_target_properties(ip_filter ip_filter_lib test_ip_filter PROPERTIES
                      COMPILE_FLAGS "/W4")
endif()

set_target_properties(test_ip_filter PROPERTIES
                      COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
                      INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

target_link_libraries(ip_filter ip_filter_lib)

target_link_libraries(test_ip_filter ${Boost_LIBRARIES} ip_filter_lib)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT 1@1.ru)

include(CPack)

enable_testing()

add_test(test_ip_filter test_ip_filter)
