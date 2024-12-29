#!/bin/bash

cp -r ./assets ./bin/Debug

./premake.sh
make clean
make config=debug