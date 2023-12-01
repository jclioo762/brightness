#!/bin/bash
rm -rf build/
rm -rf cmake-build-debug/
sudo rm -f  /usr/lib/dde-dock/plugins/libbrightness.so
pkill dde-dock
dde-dock
