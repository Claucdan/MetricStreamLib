cmake_minimum_required(VERSION 3.10)
project(MetricStreamLib
        VERSION 1.0.0
        DESCRIPTION "Metric collection and saver library"
        HOMEPAGE_URL ""
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

if (NOT SOURCE_FILES)
    message(FATAL_ERROR "No source files found!")
endif ()

add_library(MetricStreamLib STATIC ${SOURCE_FILES}
        src/metrics/Metric.cpp)

add_subdirectory(lib)

target_include_directories(MetricStreamLib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/metrics
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storage
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storage/impl
)

target_include_directories(MetricStreamLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/metrics
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storage
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storage/impl
)

target_link_libraries(MetricStreamLib PUBLIC
        SimpleLogger
        SimpleTimeFormat
)

option(BUILD_EXAMPLES "Build examples" ON)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()