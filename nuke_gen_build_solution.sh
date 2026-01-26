#!/usr/bin/env bash
rm -rf build

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

if [[ "$TRACY" == "ON" ]]; then
  ./gen_build_solution.sh "$BUILD_TYPE" tracy
else
  ./gen_build_solution.sh "$BUILD_TYPE" no-tracy
fi
