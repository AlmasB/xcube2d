#include "GraphicsEngine.h"

SDL_Renderer * GraphicsEngine::renderer = nullptr;

GraphicsEngine::GraphicsEngine() : fpsAverage(0), fpsPrevious(0), fpsStart(0), fpsEnd(0), drawColor(toSDLColor(0, 0, 0, 255)) {
	window = SDL_CreateWindow("The X-CUBE 2D Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (nullptr == window)
		throw EngineException("Failed to create window", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (nullptr == renderer)
		throw EngineException("Failed to create renderer", SDL_GetError());

	// although not necessary, SDL doc says to prevent hiccups load it before using
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		throw EngineException("Failed to init SDL_image - PNG", IMG_GetError());

	if (TTF_Init() < 0)
		throw EngineException("Failed to init SDL_ttf", TTF_GetError());
}

GraphicsEngine::~GraphicsEngine() {
#ifdef __DEBUG
	debug("GraphicsEngine::~GraphicsEngine() started");
#endif

	IMG_Quit();
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();

#ifdef __DEBUG
	debug("GraphicsEngine::~GraphicsEngine() finished");
#endif
}

void GraphicsEngine::setWindowTitle(const char * title) {
	SDL_SetWindowTitle(window, title);
#ifdef __DEBUG
	debug("Set window title to:", title);
#endif
}

void GraphicsEngine::setWindowTitle(const std::string & title) {
	SDL_SetWindowTitle(window, title.c_str());
#ifdef __DEBUG
	debug("Set window title to:", title.c_str());
#endif
}

void GraphicsEngine::setWindowIcon(const char *iconFileName) {
	SDL_Surface * icon = IMG_Load(iconFileName);
	if (nullptr == icon) {
		std::cout << "Failed to load icon: " << iconFileName << std::endl;
		std::cout << "Aborting: GraphicsEngine::setWindowIcon()" << std::endl;
		return;
	}
	SDL_SetWindowIcon(window, icon);
#ifdef __DEBUG
	debug("Set Window Icon to", iconFileName);
#endif
	SDL_FreeSurface(icon);
}

void GraphicsEngine::setFullscreen(bool b) {
	SDL_SetWindowFullscreen(window, b ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_MAXIMIZED);
}

void GraphicsEngine::setVerticalSync(bool b) {
	if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, b ? "1" : "0")) {
		std::cout << "Failed to set VSYNC" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
#ifdef __DEBUG
	debug("Current VSYNC:", SDL_GetHint(SDL_HINT_RENDER_VSYNC));
#endif
}

void GraphicsEngine::setDrawColor(const SDL_Color & color) {
	drawColor = color;
	SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, 255);	// may need to be adjusted for allowing alpha
}

void GraphicsEngine::setWindowSize(const int &w, const int &h) {
	SDL_SetWindowSize(window, w, h);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
#ifdef __DEBUG
	debug("Set Window W", w);
	debug("Set Window H", h);
#endif
}

Dimension2i GraphicsEngine::getCurrentWindowSize() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return Dimension2i(w, h);
}

Dimension2i GraphicsEngine::getMaximumWindowSize() {
	SDL_DisplayMode current;
	if (SDL_GetCurrentDisplayMode(0, &current) == 0) {
		return Dimension2i(current.w, current.h);
	}
	else {
		std::cout << "Failed to get window data" << std::endl;
		std::cout << "GraphicsEngine::getMaximumWindowSize() -> return (0, 0)" << std::endl;
		return Dimension2i();
	}
}

void GraphicsEngine::showInfoMessageBox(const std::string & info, const std::string & title) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), info.c_str(), window);
}

void GraphicsEngine::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, 255);	// may need to be adjusted for allowing alpha
}

void GraphicsEngine::showScreen() {
	SDL_RenderPresent(renderer);
}

void GraphicsEngine::useFont(TTF_Font * _font) {
	if (nullptr == _font) {
#ifdef __DEBUG
		debug("GraphicsEngine::useFont()", "font is null");
#endif
		return;
	}

	font = _font;
}

void GraphicsEngine::setFrameStart() {
	fpsStart = SDL_GetTicks();
}

void GraphicsEngine::adjustFPSDelay(const Uint32 &delay) {
	fpsEnd = SDL_GetTicks() - fpsStart;
	if (fpsEnd < delay) {
		SDL_Delay(delay - fpsEnd);
	}

	Uint32 fpsCurrent = 1000 / (SDL_GetTicks() - fpsStart);
	fpsAverage = (fpsCurrent + fpsPrevious + fpsAverage * 8) / 10;	// average, 10 values / 10
	fpsPrevious = fpsCurrent;
}

Uint32 GraphicsEngine::getAverageFPS() {
	return fpsAverage;
}

SDL_Texture * GraphicsEngine::createTextureFromSurface(SDL_Surface * surf) {
	return SDL_CreateTextureFromSurface(renderer, surf);
}

SDL_Texture * GraphicsEngine::createTextureFromString(const std::string & text, TTF_Font * _font, SDL_Color color) {
	SDL_Texture * textTexture = nullptr;
	SDL_Surface * textSurface = TTF_RenderText_Blended(_font, text.c_str(), color);
	if (textSurface != nullptr) {
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
	}
	else {
		std::cout << "Failed to create texture from string: " << text << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}

	return textTexture;
}

void GraphicsEngine::setDrawScale(const Vector2f & v) {
	SDL_RenderSetScale(renderer, v.x, v.y);
}

/* ALL DRAW FUNCTIONS */
/* overloads explicitly call SDL funcs for better performance hopefully */

void GraphicsEngine::drawRect(const Rectangle2 & rect) {
	SDL_RenderDrawRect(renderer, &rect.getSDLRect());
}

void GraphicsEngine::drawRect(const Rectangle2 & rect, const SDL_Color & color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawRect(renderer, &rect.getSDLRect());
	SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, 255);
}

void GraphicsEngine::drawRect(SDL_Rect * rect, const SDL_Color & color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawRect(renderer, rect);
	SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, 255);
}

void GraphicsEngine::drawRect(SDL_Rect * rect) {
	SDL_RenderDrawRect(renderer, rect);
}

void GraphicsEngine::drawRect(const int &x, const int &y, const int &w, const int &h) {
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}

void GraphicsEngine::fillRect(SDL_Rect * rect) {
	SDL_RenderFillRect(renderer, rect);
}

void GraphicsEngine::fillRect(const int &x, const int &y, const int &w, const int &h) {
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void GraphicsEngine::drawPoint(const Point2 & p) {
	SDL_RenderDrawPoint(renderer, p.x, p.y);
}

void GraphicsEngine::drawLine(const Line2i & line) {
	SDL_RenderDrawLine(renderer, line.start.x, line.start.y, line.end.x, line.end.y);
}

void GraphicsEngine::drawLine(const Point2 & p0, const Point2 & p1) {
	SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
}

void GraphicsEngine::drawCircle(const Point2 & center, const float & radius) {
	for (float i = 0.0f; i < 2*M_PI; i += PI_OVER_180) {
		int x = (int)(center.x + radius * cos(i));
		int y = (int)(center.y + radius * sin(i));
		SDL_RenderDrawPoint(renderer, x, y);
	}
}

void GraphicsEngine::drawEllipse(const Point2 & center, const float & radiusX, const float & radiusY) {
	for (float i = 0.0f; i < 2 * M_PI; i += PI_OVER_180) {
		int x = (int)(center.x + radiusX * cos(i));
		int y = (int)(center.y + radiusY * sin(i));
		SDL_RenderDrawPoint(renderer, x, y);
	}
}

void GraphicsEngine::drawTexture(SDL_Texture * texture, SDL_Rect * src, SDL_Rect * dst, const double & angle, const SDL_Point * center, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(renderer, texture, src, dst, angle, center, flip);
}

void GraphicsEngine::drawTexture(SDL_Texture * texture, SDL_Rect * dst, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(renderer, texture, 0, dst, 0.0, 0, flip);
}

void GraphicsEngine::drawText(const std::string & text, const int &x, const int &y) {
	SDL_Texture * textTexture = createTextureFromString(text, font, drawColor);
	int w, h;
	SDL_QueryTexture(textTexture, 0, 0, &w, &h);
	SDL_Rect dst = { x, y, w, h };
	drawTexture(textTexture, &dst);
	SDL_DestroyTexture(textTexture);
}