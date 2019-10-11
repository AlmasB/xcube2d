#include "TestMazeGenerator.h"

Dir::Dir() {}

Dir::Dir(const Dir & other) : bit(other.bit), dx(other.dx), dy(other.dy),
opposite(other.opposite) {}

MazeGenerator::MazeGenerator(const int & x, const int & y) : x(x), y(y) {
	N.bit = 1;
	N.dx = 0;
	N.dy = -1;
	N.opposite = &S;

	S.bit = 2;
	S.dx = 0;
	S.dy = 1;
	S.opposite = &N;

	E.bit = 4;
	E.dx = 1;
	E.dy = -0;
	E.opposite = &W;

	W.bit = 8;
	W.dx = -1;
	W.dy = 0;
	W.opposite = &E;

	maze = new int*[x];

	for (int i = 0; i < x; ++i)
		maze[i] = new int[y];

	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			maze[i][j] = 0;
		}
	}
}

MazeGenerator::~MazeGenerator() {
	for (int i = 0; i < x; ++i)
		delete[] maze[i];
	delete[] maze;
}

void MazeGenerator::generateMaze(int cx, int cy) {
	Dir * dirs = new Dir[4] {N, S, E, W};

	for (int i = 0; i < 4; ++i) {
		int index;
		do {
			index = getRandom(0, 3);
		} 
		while (index == i);

		Dir tmp = dirs[i];
		dirs[i] = dirs[index];
		dirs[index] = tmp;
	}

	for (int i = 0; i < 4; ++i) {
		Dir dir = dirs[i];
		int nx = cx + dir.dx;
		int ny = cy + dir.dy;
		if (between(nx, x) && between(ny, y) && (maze[nx][ny] == 0)) {
			maze[cx][cy] |= dir.bit;
			maze[nx][ny] |= dir.opposite->bit;
			generateMaze(nx, ny);
		}
	}
}
