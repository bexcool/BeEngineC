cp ../BeEngine/bin/Debug/libBeEngine.dylib ./libs/BeEngine/lib/libBeEngine.dylib

./premake.sh
make clean
make config=debug