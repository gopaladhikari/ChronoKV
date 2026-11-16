cmake_minimum_required(VERSION 3.24)

project(ChronoKV VERSION 1.0 LANGUAGES CXX)

set(SOURCE_FILES 
  src/main.cpp
  src/hello.cpp
)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(ChronoKV ${SOURCE_FILES})

# Tell the compiler where to find your .h header files
target_include_directories(ChronoKV PRIVATE include)