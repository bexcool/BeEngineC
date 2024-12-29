#!/bin/bash

cp -r ./assets ./bin/Release

./premake.sh
make clean
make config=release