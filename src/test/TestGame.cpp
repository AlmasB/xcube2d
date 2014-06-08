#include "TestGame.h"

TestGame::TestGame() : AbstractGame() {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/BowlingShoes.ttf", 72);
	gfx->useFont(font);
}

TestGame::~TestGame() {

}

void TestGame::handleKeyEvents() {

}

void TestGame::update() {

}

void TestGame::render() {
	gfx->setDrawColor(SDL_COLOR_WHITE);
	gfx->drawRect(100, 100, 50, 50);

	gfx->setDrawColor(SDL_COLOR_PURPLE);
	gfx->drawRect(300, 300, 50, 50);

	gfx->setDrawColor(SDL_COLOR_BLUE);
	gfx->drawRect(245, 190, 34, 35);

	gfx->setDrawColor(SDL_COLOR_ORANGE);
	gfx->drawText("Testing", 250, 200);

	
}