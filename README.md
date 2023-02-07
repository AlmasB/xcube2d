xcube2d
=======

A simple 2D game engine based on SDL 2.0 to teach core game elements.

### Dependencies

To simplify development, the following libraries are included:

* SDL 2.0.9
* SDL_image 2.0.5
* SDL_mixer 2.0.4
* SDL_ttf 2.0.15

### Build

The project is configured to be developed on Windows, so it only includes Windows-specific SDL versions, however you should be able to build on Linux and Mac OS by getting appropriate SDL distributions.

To build, you will need:

* [CMake](https://github.com/Kitware/CMake/releases/download/v3.24.2/cmake-3.24.2-windows-x86_64.zip) 3.24+
* Visual Studio 2022

1. Download this repository by clicking "Clone or download" -> Download zip.
2. Extract the zip file and rename `xcube2d-master` to `xcube`.

Open the command line (via [Git Bash](https://gitforwindows.org/) (git for windows")):

```
cd xcube
mkdir build
cd build

PATH_WHERE_DOWNLOADED_CMAKE/bin/cmake.exe .. -G "Visual Studio 17 2022"

```

After this, a ".sln" will be generated in `build/`.

1. Open the ".sln" file with Visual Studio 2022.
2. Right click on MyGame in project explorer and select as startup project.
3. Right click on MyGame again and select Properties.
4. In the properties window, Linker -> System and change SubSystem to Console.
5. Copy the `res/` directory to the `build` directory.

You can now run the demo from Visual Studio via Local Windows Debugger.

### Task

**Read the assignment brief!**

You should only modify:

* MyEngineSystem.h
* MyEngineSystem.cpp
* MyGame.h
* MyGame.cpp