#!/bin/bash

#cd ../
mkdir build
cd build/ || exit
rm -rf * || exit
cmake .. || exit
make -j8 || exit
