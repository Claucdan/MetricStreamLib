cmake_minimum_required(VERSION 3.10)

project(MetricStreamExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Basic example.cpp
        example-metrics/CPUMetric.cpp
        example-metrics/CPUMetric.h
        example-metrics/MemoryMetric.cpp
        example-metrics/MemoryMetric.h)
target_link_libraries(Basic PRIVATE

        MetricStreamLib)