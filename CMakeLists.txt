cmake_minimum_required(VERSION 3.10)
project(classroom-manager)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug) 

add_executable(main
    src/main.cpp
    src/models/myfile.cpp
    src/models/indexfilerow.cpp
    src/models/hash.cpp
    src/models/myregex.cpp
    src/models/person.cpp
    src/models/student.cpp
    src/models/classroom.cpp
)

include_directories(include)

add_custom_target(run
    COMMAND main STUDENTS_FILENAME INDEX_FILENAME MAX_STUDENTS
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
