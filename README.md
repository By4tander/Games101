# Games101
Games101 Homework Framework

## Build Instruction

First, recursive clone this repository with submodules:
```bash
git clone --recursive https://github.com/BFU-Graphics/GAMES101.git
```

Then, make sure you installed global opencv dependency
- For Windows users, install opencv with `vcpkg install opencv:x64-windows`, then alter the `vcpkg.cmake` path in every root `CMakeLists.txt`
- For MacOS users, install opencv with `brew install opencv`
- For Ubuntu users, install opencv with `sudo apt install libopencv-dev`

Load the project with CLion, and build it.

Have fun with Graphics.