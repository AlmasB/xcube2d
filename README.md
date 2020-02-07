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

* [CMake](https://cmake.org/) 3.6+
* Visual Studio 2017+

1. Download this repository by clicking "Clone or download" -> Download zip.
2. Extract the zip file and rename `xcube2d-master` to `xcube`.

Open the command line (via Git Bash):

```
cd xcube2d
mkdir build
cd build

// Note: if running on Uni machines, it's /c/Program\ Files/CMake/bin/cmake rather than just cmake
// Note: if running with Visual Studio 2019, then change 15 to 16 and 2017 to 2019

cmake .. -G "Visual Studio 15 2017 Win64"

```

After this, a ".sln" will be generated in `build/`.

1. Open the ".sln" file with Visual Studio 2017+.
2. Right click on MyGame in project explorer and select as startup project.
3. Right click on MyGame again and select Properties.
4. In the properties window, Linker -> System and change SubSystem to Console.
5. Copy the `res/` directory to the `build` directory.

You can now run the demo from Visual Studio via Local Windows Debugger.