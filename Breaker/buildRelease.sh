cp ../BeEngine/bin/Release/libBeEngine.dylib ./libs/BeEngine/lib/libBeEngine.dylib

./premake.sh
make clean
make config=release