#ifndef __GFX_ENGINE_H__
#define __GFX_ENGINE_H__

#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../core/EngineCommon.h"
#include "../math/GameMath.h"

/* ENGINE DEFAULT SETTINGS */
static const int DEFAULT_WINDOW_WIDTH = 800;
static const int DEFAULT_WINDOW_HEIGHT = 600;

static const SDL_Color SDL_COLOR_GRAY	= { 0x80, 0x80, 0x80 };
static const SDL_Color SDL_COLOR_YELLOW = { 0xFF, 0xFF, 0 };
static const SDL_Color SDL_COLOR_RED	= { 0xFF, 0, 0 };
static const SDL_Color SDL_COLOR_GREEN	= { 0, 0xFF, 0 };
static const SDL_Color SDL_COLOR_BLUE	= { 0, 0, 0xFF };
static const SDL_Color SDL_COLOR_BLACK = { 0, 0, 0 };
static const SDL_Color SDL_COLOR_WHITE = { 0xFF, 0xFF, 0xFF };
static const SDL_Color SDL_COLOR_AQUA = { 0, 0xFF, 0xFF };
static const SDL_Color SDL_COLOR_ORANGE = { 0xFF, 0xA5, 0 };
static const SDL_Color SDL_COLOR_PINK = { 0xFF, 0xC0, 0xCB };
static const SDL_Color SDL_COLOR_PURPLE = { 0x80, 0, 0x80 };
static const SDL_Color SDL_COLOR_VIOLET = { 0xEE, 0x82, 0xEE };

inline SDL_Color getRandomColor(int minRGB, int maxRGB) {
	SDL_Color color = { (Uint8)getRandom(minRGB, maxRGB), (Uint8)getRandom(minRGB, maxRGB), (Uint8)getRandom(minRGB, maxRGB) };
	return color;
}

struct SDL_Colorf {
	float r, g, b, a;
};

inline SDL_Colorf toSDLColorf(SDL_Color color) {
	SDL_Colorf colorf = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
	return colorf;
}

class GraphicsEngine {
	friend class XCube2Engine;
	private:
		SDL_Window * window;
		SDL_Renderer * renderer;

		TTF_Font * font;

		SDL_Surface * textureBackground;

		Uint32 fpsAverage, fpsPrevious, fpsStart, fpsEnd;

		GraphicsEngine();
		void initGL();

	public:	
		~GraphicsEngine();

		void useFont(TTF_Font * font);

		/**
		* Clears everything on the screen
		* Call this before drawing anything to screen
		*/
		void clearScreen();

		/**
		* Displays everything rendered on the screen
		* Call this method after you have finished drawing
		*/
		void showScreen();

		/*void drawText(std::string text, SDL_Color color, float x, float y);
		
		void drawSDLSurface(SDL_Surface * surf, float x, float y);
		void drawSDLSurface(SDL_Surface * surf, float x, float y, int w, int h);*/

		void setWindowIcon(const char *);
		void setWindowSize(const int &, const int &);
		void setWindowTitle(const char *title);
		void setWindowTitle(const std::string &);
		void setFullscreen(bool);
		void setVerticalSync(bool);

		/**
		* @return current window's dimension
		*/
		Dimension2i getCurrentWindowSize();
		/**
		* @return current display mode's resolution
		*         since most displays use native (max) resolution
		*         this returns maximum available (the one you can set) window size
		*/
		Dimension2i getMaximumWindowSize();

		void setFrameStart();
		void adjustFPSDelay(const Uint32 &);
		Uint32 getAverageFPS();

		static SDL_Texture * createTextureFromSurface(SDL_Surface *);
};

typedef GraphicsEngine GFX;

#endif
