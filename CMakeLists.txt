cmake_minimum_required(VERSION 3.31.6)
project(0_build_a_cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(execute)
include_directories(structure)
include_directories(assets)

add_executable(0_build_a_cli
        assets/start.txt
        execute/CliEnv.cpp
        execute/CliEnv.h
        main.cpp
        execute/call.cpp
        execute/call.h
        structure/Task.cpp
        structure/Task.h
        structure/Qeue.cpp
        structure/Qeue.h
)
