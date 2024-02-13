@echo off

rem Build config
rem cmake -S . -B build

rem Project compile
cmake --build build

rem Execute program
cd build/debug
main.exe ../../data/STUDENTS.dat ../../data/INDEX.dat 31

rem Execution of this file
rem cmd /c build.bat