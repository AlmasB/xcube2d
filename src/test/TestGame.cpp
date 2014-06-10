#include "TestGame.h"

TestGame::TestGame() : AbstractGame(), score(0), lives(3), keys(5), gameWon(false) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/3dlet.ttf", 72);
	gfx->useFont(font);

	box = std::make_shared<SDL_Rect>();
	box->w = 30;
	box->h = 30;
	box->x = 5;
	box->y = 5;

	light = std::make_shared<SDL_Rect>();
	light->w = 150;
	light->h = 150;
	light->x = box->x - 60;
	light->y = box->y - 60;

	gfx->setVerticalSync(true);

	gen = new MazeGenerator(10, 10);
	gen->generateMaze(0, 0);


	int dist = 40;

	for (int i = 0; i < gen->y; ++i) {
		for (int j = 0; j < gen->x; ++j) {
			if ((gen->maze[j][i] & 1) == 0) {
				std::shared_ptr<Line> line = std::make_shared<Line>();
				line->start = Point2(j*dist, i * dist);
				line->end = Point2(j*dist + dist, i * dist);

				lines.push_back(line);
			}
				
			//gfx->drawLine(Point2(j*dist, i * dist), Point2(j*dist + dist, i * dist));

			if ((gen->maze[j][i] & 8) == 0) {
				std::shared_ptr<Line> line = std::make_shared<Line>();
				line->start = Point2(j*dist, i * dist);
				line->end = Point2(j*dist, i * dist + dist);

				lines.push_back(line);
			}

			//gfx->drawLine(Point2(j*dist, i * dist), Point2(j*dist, i * dist + dist));

			if (keys > 0 && getRandom(0, 100) <= 5) {
				std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
				k->alive = true;
				k->pos = Point2(j*dist + dist/2, i*dist + dist/2);
				points.push_back(k);
				keys--;
			}
		}

		std::shared_ptr<Line> line = std::make_shared<Line>();
		line->start = Point2(gen->x * dist, i * dist);
		line->end = Point2(gen->x * dist, i * dist + dist);

		lines.push_back(line);

		//gfx->drawLine(Point2(gen->x * dist, i * dist), Point2(gen->x * dist, i * dist + dist));
	}

	for (int j = 0; j < gen->x; j++) {
		std::shared_ptr<Line> line = std::make_shared<Line>();
		line->start = Point2(j * dist, gen->y * dist);
		line->end = Point2(j * dist + dist, gen->y * dist);

		lines.push_back(line);

		//gfx->drawLine(Point2(j * dist, gen->y * dist), Point2(j * dist + dist, gen->y * dist));
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
	box->x += velocity.x;
	for (auto line : lines) {
		if (isColliding(box.get(), line)) {
			box->x -= velocity.x;
			break;
		}
	}

	box->y += velocity.y;
	for (auto line : lines) {
		if (isColliding(box.get(), line)) {
			box->y -= velocity.y;
			break;
		}
	}

	for (auto key : points) {
		if (key->alive && isColliding(box.get(), key->pos)) {
			score += 200;
			key->alive = false;
			keys--;
		}
	}

	velocity = Vector2i(0, 0);
	light->x = box->x - 60;
	light->y = box->y - 60;

	if (keys == 0)
		gameWon = true;

}

void TestGame::render() {
	gfx->setDrawColor(SDL_COLOR_WHITE);
	for (auto line : lines)
		if (isColliding(light.get(), line))
			gfx->drawLine(line->start, line->end);
	

	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box.get());

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : points)
		if (key->alive && isColliding(light.get(), key->pos))
			gfx->drawPoint(key->pos);

	gfx->drawEllipse(Point2(500, 500), 50.0f, 100.0f);

	// UI
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length()*50, 25);

	if (gameWon)
		gfx->drawText("YOU WON DEMO LOL", 50, 500);
}

bool TestGame::isColliding(const SDL_Rect * rect, std::shared_ptr<Line> line) {
	int x1 = line->start.x, y1 = line->start.y, x2 = line->end.x, y2 = line->end.y;
	return SDL_IntersectRectAndLine(rect, &x1, &y1, &x2, &y2) == 1;
}

bool TestGame::isColliding(const SDL_Rect * rect, Point2 p) {
	Rectangle2 r = { rect->x, rect->y, rect->w, rect->h };
	return r.contains(p);
}