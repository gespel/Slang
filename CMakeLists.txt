cmake_minimum_required(VERSION 3.9)

project(slang VERSION 1.0.1 DESCRIPTION "Slang Language Library")

# Für macOS: Universal Binary (Intel + Apple Silicon)
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(slang SHARED
        core/src/function.c
        core/src/interpreter.c
        core/src/tokenizer.c
        core/src/tools.c
        core/src/rack.c core/src/buffer_core.c
)

set_target_properties(slang PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(slang PRIVATE core/include)
target_include_directories(slang PRIVATE core/src)

include(GNUInstallDirs)

install(TARGETS slang
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})