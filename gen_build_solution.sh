#!/usr/bin/env bash
BUILD_TYPE="${1:-Release}"

case "$BUILD_TYPE" in
  [Dd]ebug)   BUILD_TYPE="Debug" ;;
  [Rr]elease) BUILD_TYPE="Release" ;;
esac

cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

./build_solution.sh
