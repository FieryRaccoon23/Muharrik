@echo off
rmdir /s /q build

set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Release

if /I "%BUILD_TYPE%"=="debug" set BUILD_TYPE=Debug
if /I "%BUILD_TYPE%"=="release" set BUILD_TYPE=Release

call gen_build_solution.bat %BUILD_TYPE%