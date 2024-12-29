#!/bin/bash

cp -r ./src/assets ./bin/Debug

./premake.sh
make clean
make config=debug