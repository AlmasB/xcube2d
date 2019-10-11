#ifndef __ABSTRACT_GAME_H__
#define __ABSTRACT_GAME_H__

#include "XCube2d.h"

class AbstractGame {
	private:
		void handleMouseEvents();
		void updatePhysics();

	protected:
		AbstractGame();
		virtual ~AbstractGame();

		/* Engine systems */
		std::shared_ptr<GraphicsEngine> gfx;
		std::shared_ptr<AudioEngine> sfx;
		std::shared_ptr<EventEngine> eventSystem;
		std::shared_ptr<PhysicsEngine> physics;

		/* Main loop control */
		bool running;
        bool paused;
		double gameTime;

		virtual void handleKeyEvents() = 0;

		virtual void onLeftMouseButton();
		virtual void onRightMouseButton();

		virtual void update() = 0;
		virtual void render() = 0;

		virtual void renderUI();

		void pause()  { paused = true;  }
		void resume() { paused = false; }
	public:
		int runMainLoop();
};

#endif