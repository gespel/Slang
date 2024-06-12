cmake_minimum_required(VERSION 3.9)

project(slang VERSION 0.0.1 DESCRIPTION "slang lib description")

set(CMAKE_BUILD_TYPE Release)

include_directories(core/include)

add_library(slang SHARED
        core/src/core.c
        core/src/tokenizer.c
        core/src/interpreter.c
)


set_target_properties(slang PROPERTIES PUBLIC_HEADER slang-lib.h)