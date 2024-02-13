# C++ Classroom Manager Project

This C++ project is a simple classroom manager that allows you to perform various operations related to students in a classroom. The program uses file handling, hashing, and regular expressions to manage student data efficiently.

## Prerequisites

Ensure you have the following tools installed on your system:

- C++ compiler (e.g., [g++](https://gcc.gnu.org/))
- [CMake](https://cmake.org/)

The project uses C++14 features.

## Project Structure

- `main.cpp`: The main entry point of the program.
- `myfile.h`: Class definition for handling file operations.
- `myfile.cpp`: Implementation of file handling methods.
- `hash.h`: Class definition for hash functions.
- `hash.cpp`: Implementation of hash functions.
- `indexfilerow.h`: Class definition for index file rows.
- `indexfilerow.cpp`: Implementation of index file row methods.
- `myregex.h`: Class definition for regular expressions.
- `myregex.cpp`: Implementation of regular expression methods.
- `person.h`: Class definition for the base person class.
- `person.cpp`: Implementation of person class methods.
- `student.h`: Class definition for the student class, derived from the person class.
- `student.cpp`: Implementation of student class methods.
- `classroom.h`: Class definition for the class management.
- `classroom.cpp`: Implementation of class management methods.

## Build and Run

### Windows

1. Configure the build using CMake:

    ```
    cmake -S . -B build
    ```

2. Compile the project:

    ```
    cmake --build build
    ```

3. Execute the application:

    ```
    cd build/debug
    main.exe [STUDENTS_FILEPATH] [INDEX_FILEPATH] [MAX_NUMBER_OF_STUDENTS]
    ```

### Linux

1. Configure the build using CMake:

    ```bash
    cmake -S . -B build
    ```

2. Compile the project:

    ```bash
    cmake --build build
    ```

3. Execute the application:

    ```bash
    cd build/debug
    ./main [STUDENTS_FILEPATH] [INDEX_FILEPATH] [MAX_NUMBER_OF_STUDENTS]
    ```

## Functionality

The program allows you to perform the following operations:

1. Display the list of students in the class.
2. Add a new student to the class.
3. Search for a student by name and surname.
4. Search for a student by telephone number.

Follow the on-screen instructions to navigate through the options.
