# Game of Life on the micro:bit

This repository contains a Just For Fun (JFF) implementation of Conway's Game of Life for the micro:bit.
It is an experiment if we can use xtensor for embedded development. This could lead to other very 
interesting applications, for example, using xtensor as part of a toolchain to implement embedded control
algorithms.

Note: the following requires `yotta` to be installed. Read up on the micro:bit docs how to make that happen: https://lancaster-university.github.io/microbit-docs/offline-toolchains/

To build this application, execute:

```bash
yotta target bbc-microbit-classic-gcc-nosd
yotta up
# Now you need to patch cmake to allow exceptions
# Go to ./yotta_targets/bbc-microbit-classic-gcc-nosd/CMake/toolchain.cmake
# and add set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")
# you will also have to adjust the xtensor and xtl paths in module.json at extraIncludes
yotta build
cp build/bbc-microbit-classic-gcc-nosd/source/xtensor-microbit.hex >>/your/microbit/folder/<<
``` 
