@echo off
set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Release

if /I "%BUILD_TYPE%"=="debug" set BUILD_TYPE=Debug
if /I "%BUILD_TYPE%"=="release" set BUILD_TYPE=Release

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++

call build_solution.bat %BUILD_TYPE%
