#ifndef __GAME_MATH_H__
#define __GAME_MATH_H__

#include <cstdlib>

#include <SDL_rect.h>

static const float PI_OVER_180 = (float)(3.14159265358979323846 / 180.0f);
static const float _180_OVER_PI = (float)(180.0f / 3.14159265358979323846);

inline float toRadians(float deg) {
	return deg * PI_OVER_180;
}

inline float toDegrees(float rad) {
	return rad * _180_OVER_PI;
}

struct Vector2f {
	float x;
	float y;

	Vector2f() : Vector2f(0.0f, 0.0f) {}
	Vector2f(float x, float y) : x(x), y(y) {}
};

struct Vector2i {
	int x;
	int y;

	Vector2i() : Vector2i(0, 0) {}
	Vector2i(int x, int y) : x(x), y(y) {}
};

struct Point2 {
	int x, y;

	Point2() : Point2(0, 0) {}
	Point2(int x, int y) : x(x), y(y) {}

    Point2& operator+=(const Vector2f& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Point2& operator-=(const Vector2f& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
};

struct Line2i {
	Point2 start, end;

	Line2i() : Line2i(Point2(), Point2()) {}
	Line2i(const Point2 & start, const Point2 & end) : start(start), end(end) {}
};

struct Rectangle2 {
	int x, y, w, h;

	Rectangle2(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

	SDL_Rect getSDLRect() const {
		SDL_Rect rect = { x, y, w, h };
		return rect;
	}

	inline bool contains(const Point2 & p) {
		return p.x >= x && p.x <= x + w
			&& p.y >= y && p.y <= y + h;
	}

	inline bool intersects(const Rectangle2 & other) {
        SDL_Rect rect1 = getSDLRect();
        SDL_Rect rect2 = other.getSDLRect();

		return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
	}

	inline bool intersects(const Line2i & line) {
		int x1 = line.start.x, y1 = line.start.y, x2 = line.end.x, y2 = line.end.y;
		SDL_Rect rect = { x, y, w, h };
		return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2) == SDL_TRUE;
	}
};

struct Rectangle2f {
    float x, y, w, h;

    Rectangle2f(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    SDL_Rect getSDLRect() const {
        SDL_Rect rect = { x, y, w, h };
        return rect;
    }

    inline bool contains(const Point2& p) {
        return p.x >= x && p.x <= x + w
            && p.y >= y && p.y <= y + h;
    }

    inline bool intersects(const Rectangle2f& other) {
        SDL_Rect rect1 = getSDLRect();
        SDL_Rect rect2 = other.getSDLRect();

        return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
    }

    inline bool intersects(const Line2i& line) {
        int x1 = line.start.x, y1 = line.start.y, x2 = line.end.x, y2 = line.end.y;
        SDL_Rect rect = { x, y, w, h };
        return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2) == SDL_TRUE;
    }
};

typedef Rectangle2 Rect;
typedef Rectangle2f Rectf;

struct Dimension2i {
	int w, h;

	Dimension2i() : Dimension2i(0, 0) {}
	Dimension2i(int w, int h) : w(w), h(h) {}
};

/**
* Init srand() before to get different random values every time you start program
*
* @return
*			a random integer value between "min" and "max", both inclusive
*/
inline int getRandom(int min, int max) {
	return (int)(rand() % (max - min)) + min;
}

#endif
