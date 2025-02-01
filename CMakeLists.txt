cmake_minimum_required(VERSION 3.15)

project(bigint VERSION 1.0 LANGUAGES C DESCRIPTION "Basic big integer operation library")

set(CMAKE_C_FLAGS_RELEASE "-O3")

set( PROJECT_SOURCE_DIR src/ )
set( PROJECT_INCLUDE_DIR include/ )
set( EXAMPLE_DIR example/ )

file( GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/*.c )

add_library( bigint SHARED ${sources})

set_target_properties( bigint PROPERTIES VERSION ${PROJECT_VERSION} )
set_target_properties( bigint PROPERTIES PUBLIC_HEADER ${PROJECT_INCLUDE_DIR}/bigint.h )

target_include_directories( bigint PUBLIC ${PROJECT_INCLUDE_DIR})

add_executable( bigint_test ${EXAMPLE_DIR}/example.c )
target_link_libraries( bigint_test bigint )
