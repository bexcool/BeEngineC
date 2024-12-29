# BeEngine

Bla bla bla

## Compile from source
### MacOS
#### Prerequisites
- Homebrew
- Make
- Visual Studio Code or any favorite editor

#### Compiling
1. Run the "initializeProjectMacOS.sh" (This script will install **SDL2**, **SDL2_Image**, **SDL2_TTF**, **SDL2_Mixer**, **Premake**)
2. Then run "buildRelease.sh"
3. Engine is now compiled in "bin/Release/libBeEngine.dylib"

### Linux
#### Prerequisites
- Apt
- Visual Studio Code or any favorite editor

#### Compiling
1. Run the "initializeProjectLinux.sh"
2. Then run "buildRelease.sh"
3. Engine is now compiled in "bin/Release/libBeEngine.dylib"

### Windows
- Not yet supported, sorry :C

## Creating new projects
1. Compile source code
2. Run the "generateProjectTemplate.*" file to generate a project template. After that you can copy it from the "projectTemplate" folder.