#!/bin/bash

#cd ../
mkdir build
cd build/ || exit
rm -rf * || exit
cmake .. || exit
make -j6 || exit
sudo chmod 755  libbrightness.so
sudo rm -f  /usr/lib/dde-dock/plugins/libbrightness.so
sudo cp -f libbrightness.so  /usr/lib/dde-dock/plugins/
clear
pkill dde-dock
dde-dock
