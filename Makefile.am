bin_PROGRAMS = XCDemo
XCDemo_SOURCES = src/engine/audio/AudioEngine.cpp
XCDemo_SOURCES += src/engine/core/AbstractGame.cpp src/engine/core/Debug.cpp src/engine/core/ResourceManager.cpp src/engine/core/Timer.cpp src/engine/core/XCube2d.cpp
XCDemo_SOURCES += src/engine/graphics/GraphicsEngine.cpp
XCDemo_SOURCES += src/engine/input/EventEngine.cpp
XCDemo_SOURCES += src/engine/physics/PhysicsEngine.cpp

XCDemo_SOURCES += src/test/MazeGenerator.cpp src/test/TestGame.cpp src/test/Main.cpp

AM_CPPFLAGS = -std=c++11 $(sdl2_CFLAGS)
LIBS += $(sdl2_LIBS) $(SDL2_image_LIBS) $(SDL2_mixer_LIBS) $(SDL2_ttf_LIBS)