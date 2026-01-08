#!/usr/bin/env bash
rm -rf build

BUILD_TYPE="${1:-Release}"

case "$BUILD_TYPE" in
  [Dd]ebug)   BUILD_TYPE="Debug" ;;
  [Rr]elease) BUILD_TYPE="Release" ;;
esac

./gen_build_solution.sh "$BUILD_TYPE"
