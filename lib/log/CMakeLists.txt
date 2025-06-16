project(SimpleLogger)

add_library(SimpleLogger STATIC
        src/LogLevel.h
        src/Logger.cpp
        src/Logger.h
        src/imp/ConsoleLogger.cpp
        src/imp/ConsoleLogger.h
        src/imp/ConsoleLog.h
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_LOG)
endif()

target_include_directories(SimpleLogger PRIVATE
        src/
        src/imp/
)

target_include_directories(SimpleLogger PUBLIC
        src/imp/
)
target_link_libraries(SimpleLogger PRIVATE SimpleTimeFormat)
