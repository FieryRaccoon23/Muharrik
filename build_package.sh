rm -rf build-pack _CPack_Packages shippable
cmake -S . -B build-pack -DCMAKE_BUILD_TYPE=Release -DMUHARRIK_PACKAGE=ON
cmake --build build-pack
cpack --config build-pack/CPackConfig.cmake