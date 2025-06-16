# MetricStreamLib

<div align="center">
    <img src="img/logo.png" width=40%>
</div>
<br>
<div align="center">
  <img src="https://img.shields.io/badge/Linux-%23.svg?logo=linux&color=black&logoColor=yellow"/>
  <img src="https://img.shields.io/badge/macOS-%23.svg?logo=apple&color=000000&logoColor=white"/>
  <img src="https://img.shields.io/badge/Windows-%23.svg?logo=windows&color=black&logoColor=blue"/>
  <img src="https://img.shields.io/badge/-C/C++-black?logo=c&logoColor=blue">
  <img src="https://img.shields.io/badge/-CMake-black?logo=cmake&logoColor=yellow">
</div>

## Information

This is a C++ library designed for collecting and storing metrics in a human-readable text format. The library allows
you to record named events with associated values and timestamps.
Metrics can represent various system or application events such as CPU utilization or the number of HTTP requests per
second. The system is flexible and easily extensible to support new metric types.

### Output format:

```
<timestamp> <metric_name_1> <value_1> <metric_name_2> <value_2> ...
```

### Example output:

```
2025-06-01 15:00:01.653 "CPU" 0.97 "HTTP requests RPS" 42
2025-06-01 15:00:02.653 "CPU" 1.12 "HTTP requests RPS" 30
```

## Features

- Flexible metric types — new metric types can be added without changing the library’s core logic.
- Extensible interface — easily integrate your own metrics by implementing corresponding interfaces.
- Collects metrics in a multithreaded environment.

## Documentation

See: https://claucdan.github.io/MetricStreamLib/

## Requirements

- `CMake >= 3.10`
- `g++ >= 15.1` or `clang >= 20.1`

## Installation & Usage

### Build only library

```bash
git clone ...
mkdir build && cd build
cmake .. 
cmake --build .
```

Builded library you can find in `build/bin/`

### Build with examples

```bash
git clone ...
mkdir build && cd build
cmake .. -DBUILD_EXAMPLES=ON
cmake --build .
```

Examples you can find in `build/examples/`
