#!/usr/bin/env bash
BUILD_TYPE="Release"
TRACY="OFF"

for arg in "$@"; do
  case "$arg" in
    [Dd]ebug)   BUILD_TYPE="Debug" ;;
    [Rr]elease) BUILD_TYPE="Release" ;;
    tracy|TRACY|--tracy) TRACY="ON" ;;
    no-tracy|--no-tracy) TRACY="OFF" ;;
  esac
done

cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DMUHARRIK_TRACY="$TRACY"

./build_solution.sh
