#include "MenuManager.h"

void MenuButton::draw(std::shared_ptr<GraphicsEngine> gfx) {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(x, y, 200, 50);
}

void MenuText::draw(std::shared_ptr<GraphicsEngine> gfx) {
	gfx->setDrawColor(SDL_COLOR_BLUE);
	gfx->drawText(text, x, y);
}