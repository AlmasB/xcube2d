#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/core/AbstractGame.h"

class TestGame : public AbstractGame {
	private:
		void handleKeyEvents();
		void update();
		void render();
	public:
		TestGame();
		~TestGame();
};

#endif