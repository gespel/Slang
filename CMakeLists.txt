cmake_minimum_required(VERSION 3.9)

project(slang VERSION 1.0.1 DESCRIPTION "Slang Language Library")

add_library(slang SHARED
    core/src/core.c
    core/src/function.c
    core/src/interpreter.c
    core/src/tokenizer.c
    core/src/tools.c
)

set_target_properties(slang PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(slang PRIVATE core/include)
target_include_directories(slang PRIVATE core/src)

include(GNUInstallDirs)

install(TARGETS slang
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})