@echo off

rem Configura la build
rem cmake -S . -B build

rem Compila il progetto
cmake --build build

rem Esegui l'applicazione
cd build/debug
main.exe
