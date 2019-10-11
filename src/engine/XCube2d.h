#ifndef __X_CUBE_2D_H__
#define __X_CUBE_2D_H__

#include <string>
#include <vector>
#include <memory>

#include "GraphicsEngine.h"
#include "AudioEngine.h"
#include "EventEngine.h"
#include "PhysicsEngine.h"
#include "ResourceManager.h"
#include "Timer.h"

const int _ENGINE_VERSION_MAJOR = 0;
const int _ENGINE_VERSION_MINOR = 1;

class XCube2Engine {
	private:
		static std::shared_ptr<XCube2Engine> instance;
		std::shared_ptr<GraphicsEngine> gfxInstance;
		std::shared_ptr<AudioEngine> audioInstance;
		std::shared_ptr<EventEngine> eventInstance;
		std::shared_ptr<PhysicsEngine> physicsInstance;

		XCube2Engine();
	public:
		/**
		* @return the instance of game engine
		* @exception throws EngineException if init of any submodules failed
		*/
		static std::shared_ptr<XCube2Engine> getInstance();
		~XCube2Engine();

		/**
		* Quits the engine, closes all the subsystems
		*
		* All subsequent calls to any of subsystems will have undefined behaviour
		*/
		static void quit();

		/**
		* Subsystems can only be accessed via the following accessors
		* @return approriate subsystem of the engine
		*/
		std::shared_ptr<GraphicsEngine> getGraphicsEngine() { return gfxInstance; }
		std::shared_ptr<AudioEngine> getAudioEngine() { return audioInstance; }
		std::shared_ptr<EventEngine> getEventEngine() { return eventInstance; }
		std::shared_ptr<PhysicsEngine> getPhysicsEngine() { return physicsInstance; }
};

typedef XCube2Engine XEngine;

#endif