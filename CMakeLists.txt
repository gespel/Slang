cmake_minimum_required(VERSION 3.9)

project(slang-lib VERSION 0.0.1 DESCRIPTION "slang lib description")

set(CMAKE_BUILD_TYPE Release)

include_directories(core/include)

add_library(slang-lib SHARED
        core/sources/core.c
)

set_target_properties(slang-lib PROPERTIES PUBLIC_HEADER slang-lib.h)