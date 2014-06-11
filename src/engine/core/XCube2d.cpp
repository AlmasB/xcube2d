/**
 * {XCube2D Game Engine}
 * Copyright(C) { 2013-2014 }  {AlmasB}
 *
 * This program is free software; you can redistribute it and / or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110 - 1301 USA.
 */

#include "XCube2d.h"

std::shared_ptr<XCube2Engine> XCube2Engine::instance = nullptr;

XCube2Engine::XCube2Engine() {
	std::cout << "Initializing X-CUBE 2D v" << _ENGINE_VERSION_MAJOR
		<< "." << _ENGINE_VERSION_MINOR << " by Almas" << std::endl;

#ifdef __DEBUG
	#if defined(_WIN32)
		debug("WIN32");
	#elif defined(__linux__)
		debug("LINUX");
	#elif defined(__APPLE__)
		debug("MACOSX");
	#endif
#endif

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		throw EngineException("SDL_Init()", SDL_GetError());

#ifdef __DEBUG
	debug("SDL_Init() successful");
#endif

	std::cout << "Logical CPU cores: " << SDL_GetCPUCount() << std::endl;
	std::cout << "System RAM: " << SDL_GetSystemRAM() << " MB" << std::endl; // will be available in SDL 2.0.1
	std::cout << "Running on: " << SDL_GetPlatform() << std::endl;

	SDL_version compiled, linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	printf("Compiled against SDL %d.%d.%d\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("Linked against SDL %d.%d.%d\n",
		linked.major, linked.minor, linked.patch);

	Uint32 ticks = SDL_GetTicks();
	srand(ticks);	// init random seed

#ifdef __DEBUG
	debug("Inited srand() with", ticks);
#endif

	// init subsystems

	gfxInstance = std::shared_ptr<GraphicsEngine>(new GraphicsEngine());

#ifdef __DEBUG
	debug("GraphicsEngine() successful");
#endif

	audioInstance = std::shared_ptr<AudioEngine>(new AudioEngine());

#ifdef __DEBUG
	debug("AudioEngine() successful");
#endif

	eventInstance = std::shared_ptr<EventEngine>(new EventEngine());

#ifdef __DEBUG
	debug("EventEngine() successful");
#endif

	physicsInstance = std::shared_ptr<PhysicsEngine>(new PhysicsEngine());
}

XCube2Engine::~XCube2Engine() {
#ifdef __DEBUG
	debug("XCube2Engine::~XCube2Engine() started");
#endif

	ResourceManager::freeResources();

	eventInstance.reset();
	gfxInstance.reset();

#ifdef __DEBUG
	debug("XCube2Engine::~XCube2Engine() finished");
#endif
}

void XCube2Engine::quit() {
	if (instance)
		instance.reset();
}

std::shared_ptr<XCube2Engine> XCube2Engine::getInstance() {
	if (!instance)
		instance = std::shared_ptr<XCube2Engine>(new XCube2Engine());
	return instance;
}