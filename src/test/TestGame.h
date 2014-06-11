#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/core/AbstractGame.h"

#include "MazeGenerator.h"

struct Line {
	Point2 start, end;
};

struct GameKey {
	Point2 pos;
	bool alive;
};

class TestGame : public AbstractGame {
	private:
		std::shared_ptr<SDL_Rect> box;
		std::shared_ptr<SDL_Rect> light;
		Vector2i velocity;

		MazeGenerator * gen;

		std::vector<std::shared_ptr<Line>> lines;
		std::vector<std::shared_ptr<GameKey>> points;

		bool isColliding(const SDL_Rect *, std::shared_ptr<Line>);
		bool isColliding(const SDL_Rect *, const Point2 &);

		/* GAMEPLAY */
		int score, keys, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
	public:
		TestGame();
		~TestGame();
};

#endif