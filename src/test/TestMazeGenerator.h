#ifndef __MAZE_GEN_H__
#define __MAZE_GEN_H__

#include <cstdlib>
#include <iostream>

#include "../engine/GameMath.h"

class Dir;

class Dir {
	public:
		Dir();
		Dir(const Dir &);
		int bit, dx, dy;
		Dir * opposite;
};

class MazeGenerator {
	private:
		Dir N, S, E, W;

	public:
		int x, y;
		int ** maze;

		MazeGenerator(const int &, const int &);
		~MazeGenerator();

		void generateMaze(int, int);
};

static bool between(int v, int upper) {
	return v >= 0 && v < upper;
}

#endif
