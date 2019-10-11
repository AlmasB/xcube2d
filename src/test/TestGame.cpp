#include "TestGame.h"

TestGame::TestGame() : AbstractGame(), score(0), lives(3), keys(5), gameWon(false), box(5, 5, 30, 30), light(0, 0, 150, 150) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

	gen = new MazeGenerator(10, 10);
	gen->generateMaze(0, 0);

	int dist = 40;

	for (int i = 0; i < gen->y; ++i) {

		int y = i * dist;

		for (int j = 0; j < gen->x; ++j) {

			int x = j * dist;

			if ((gen->maze[j][i] & 1) == 0) {
				lines.push_back(std::make_shared<Line2i>(Point2(x, y), Point2(x+dist, y)));
			}

			if ((gen->maze[j][i] & 8) == 0) {
				lines.push_back(std::make_shared<Line2i>(Point2(x, y), Point2(x, y+dist)));
			}

			if (keys > 0 && getRandom(0, 100) <= 5) {
				std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
				k->alive = true;
				k->pos = Point2(j*dist + dist/2, i*dist + dist/2);
				points.push_back(k);
				keys--;
			}
		}

		lines.push_back(std::make_shared<Line2i>(Point2(gen->x*dist, y), Point2(gen->x*dist, y + dist)));
	}

	for (int j = 0; j < gen->x; j++) {
		int x = j * dist;
		lines.push_back(std::make_shared<Line2i>(Point2(x, gen->y * dist), Point2(x + dist, gen->y * dist)));
	}

	keys = 5;
}

TestGame::~TestGame() {
	delete gen;
}

void TestGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void TestGame::update() {
	box.x += velocity.x;
	for (auto line : lines) {
		if (box.intersects(*line)) {
			box.x -= velocity.x;
			break;
		}
	}

	box.y += velocity.y;
	for (auto line : lines) {
		if (box.intersects(*line)) {
			box.y -= velocity.y;
			break;
		}
	}

	for (auto key : points) {
		if (key->alive && box.contains(key->pos)) {
			score += 200;
			key->alive = false;
			keys--;
		}
	}

	velocity = Vector2i(0, 0);

	light.x = box.x - 60;
	light.y = box.y - 60;

	if (keys == 0) {
		gameWon = true;
	}
}

void TestGame::render() {
	gfx->setDrawColor(SDL_COLOR_WHITE);
	for (auto line : lines)
		if (light.intersects(*line))
			gfx->drawLine(line->start, line->end);
	

	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : points)
		if (key->alive && light.contains(key->pos))
			gfx->drawPoint(key->pos);
}

void TestGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}