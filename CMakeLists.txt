cmake_minimum_required(VERSION 3.16)

project(ChronoKV VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ChronoKV
    src/main.cpp
    src/CommandRouter.cpp
    src/SnapshotManager.cpp
    src/StorageEngine.cpp
)

target_include_directories(ChronoKV PRIVATE include)