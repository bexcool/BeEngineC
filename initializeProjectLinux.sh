#!/bin/bash

sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;

# Installing premake5
wget https://github.com/premake/premake-core/releases/download/v5.0.0-beta3/premake-5.0.0-beta3-linux.tar.gz
tar -xzf premake-5.0.0-beta3-linux.tar.gz
chmod +x premake5
sudo mv premake5 /usr/local/bin/
rm premake-5.0.0-beta3-linux.tar.gz.1

mkdir -p ./libs/SDL2/include
mkdir -p ./libs/SDL2/lib

cp -r /usr/include/SDL2/*.h ./libs/SDL2/include

cp -r /usr/lib/x86_64-linux-gnu/libSDL2.so ./libs/SDL2/lib
cp -r /usr/lib/x86_64-linux-gnu/libSDL2_image.so ./libs/SDL2/lib
cp -r /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so ./libs/SDL2/lib
cp -r /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so ./libs/SDL2/lib
