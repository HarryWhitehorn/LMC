cmake_minimum_required(VERSION 3.10)

project(LMC)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/utils.cpp
    src/lmc.cpp
)

add_executable(lmc ${SOURCES})
