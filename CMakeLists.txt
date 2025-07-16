cmake_minimum_required(VERSION 3.9)

project(slang VERSION 1.0.1 DESCRIPTION "Slang Language Library")

# Für macOS: Universal Binary (Intel + Apple Silicon)
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


file(GLOB MODULE_SOURCES ${CMAKE_SOURCE_DIR}/modules/src/*.c)
file(GLOB MODULE_HEADERS ${CMAKE_SOURCE_DIR}/modules/include/*.h)


add_library(slang_modules STATIC ${MODULE_SOURCES} ${MODULE_HEADERS})

target_include_directories(slang_modules PUBLIC ${CMAKE_SOURCE_DIR}/modules/include)
target_link_libraries(slang_modules PUBLIC m)


# === Slang Core Library ===

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/core/src/*.c)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/core/include/*.h)

add_library(slang STATIC ${SOURCES} ${HEADERS})


set_target_properties(slang PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(slang PRIVATE core/include)
target_include_directories(slang PRIVATE core/src)

target_link_libraries(slang PRIVATE slang_modules)

# === Installation ===

include(GNUInstallDirs)

install(TARGETS slang
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS slang_modules
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)