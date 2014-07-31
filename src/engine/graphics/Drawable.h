#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "GraphicsEngine.h"

class Drawable {
	public:
		virtual void draw(std::shared_ptr<GraphicsEngine>) = 0;
};

#endif