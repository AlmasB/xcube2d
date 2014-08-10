#ifndef __ABSTRACT_GAME_H__
#define __ABSTRACT_GAME_H__

#include "XCube2d.h"

class AbstractGame : public Runnable {
	private:
		void renderMenu();
		void handleMouseEvents();
		void updatePhysics();
		
		//static void loop();
		
		
		

	protected:
		
		AbstractGame();

		/* ENGINE OBJECTS */
		std::shared_ptr<GraphicsEngine> gfx;
		std::shared_ptr<AudioEngine> sfx;
		std::shared_ptr<EventEngine> eventSystem;
		std::shared_ptr<PhysicsEngine> physics;

		MenuManager mgr;

		/* Main loop control */
		bool running, paused;
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
		virtual ~AbstractGame();

		int runMainLoop();
		void run();
		
};

#endif