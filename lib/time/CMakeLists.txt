project(SimpleTimeFormat)

add_library(SimpleTimeFormat STATIC
        src/SimpleTimeFormat.h
        src/SimpleTimeFormat.cpp
)

target_include_directories(SimpleTimeFormat PUBLIC
        src/
)