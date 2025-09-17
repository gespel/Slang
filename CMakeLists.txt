cmake_minimum_required(VERSION 3.9)

project(slang VERSION 1.0.1 DESCRIPTION "Slang Language Library")

#add_definitions(-DSLANG_DEBUG)
if(SLANG_DEBUG)
    add_definitions(-DSLANG_DEBUG)
endif()

# Für macOS: Universal Binary (Intel + Apple Silicon)
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


file(GLOB OSC_SOURCES ${CMAKE_SOURCE_DIR}/modules/oscillators/src/*.c)
file(GLOB OSC_HEADERS ${CMAKE_SOURCE_DIR}/modules/oscillators/include/*.h)
file(GLOB DATA_SOURCES ${CMAKE_SOURCE_DIR}/modules/data/src/*.c)
file(GLOB DATA_HEADERS ${CMAKE_SOURCE_DIR}/modules/data/include/*.h)
file(GLOB STEP_SOURCES ${CMAKE_SOURCE_DIR}/modules/stepsequencer/src/*.c)
file(GLOB STEP_HEADERS ${CMAKE_SOURCE_DIR}/modules/stepsequencer/include/*.h)
file(GLOB SAMPLE_SOURCE_HEADERS ${CMAKE_SOURCE_DIR}/modules/sample-source/include/*.h)
file(GLOB SAMPLE_SOURCE_SOURCES ${CMAKE_SOURCE_DIR}/modules/sample-source/src/*.c)




add_library(slang_modules STATIC ${DATA_SOURCES} ${DATA_HEADERS} ${OSC_SOURCES} ${OSC_HEADERS} ${STEP_SOURCES} ${STEP_HEADERS} ${SAMPLE_SOURCE_HEADERS} ${SAMPLE_SOURCE_SOURCES})

target_include_directories(slang_modules PUBLIC ${CMAKE_SOURCE_DIR}/modules/include)
target_link_libraries(slang_modules PUBLIC m)


# === Slang Core Library ===

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/core/src/*.c)
#file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/core/include/*.h)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/slang-lib.h)

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