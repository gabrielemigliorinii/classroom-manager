cmake_minimum_required(VERSION 3.10)
project(classroom-manager)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug) 

add_executable(main
    src/main.cpp
    src/models/person.cpp
    src/models/myregex.cpp
)

include_directories(include)
include_directories(src)
