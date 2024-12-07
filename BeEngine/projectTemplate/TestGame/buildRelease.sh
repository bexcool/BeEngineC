#!/bin/bash

cp -r ./src/assets ./bin/Release

./premake.sh
make clean
make config=release