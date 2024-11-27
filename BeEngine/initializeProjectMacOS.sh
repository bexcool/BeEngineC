brew install sdl2 sdl2_image sdl2_ttf

mkdir -p ./libs/SDL2/include
mkdir -p ./libs/SDL2/lib

cp -r $(brew --prefix sdl2)/include/SDL2/*.h ./libs/SDL2/include
cp -r $(brew --prefix sdl2_image)/include/SDL2/*.h ./libs/SDL2/include
cp -r $(brew --prefix sdl2_ttf)/include/SDL2/*.h ./libs/SDL2/include

cp -r $(brew --prefix sdl2)/lib/libSDL2.dylib ./libs/SDL2/lib
cp -r $(brew --prefix sdl2_image)/lib/libSDL2_image.dylib ./libs/SDL2/lib
cp -r $(brew --prefix sdl2_ttf)/lib/libSDL2_ttf.dylib ./libs/SDL2/lib