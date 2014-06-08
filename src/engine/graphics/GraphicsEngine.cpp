#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() : fpsAverage(0), fpsPrevious(0), fpsStart(0), fpsEnd(0) {
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

	textureBackground = IMG_Load("res/trans128.png");
	if (nullptr == textureBackground)
		throw EngineException("Failed to load texture background", IMG_GetError());
}

GraphicsEngine::~GraphicsEngine() {
#ifdef __DEBUG
	debug("GraphicsEngine::~GraphicsEngine() started");
#endif

	SDL_FreeSurface(textureBackground);
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
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, b ? "1" : "0");
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
		return Dimension2i(0, 0);
	}
}

void GraphicsEngine::clearScreen() {
	SDL_RenderClear(renderer);
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