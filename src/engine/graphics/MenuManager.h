#ifndef __MENU_MANAGER_H__
#define __MENU_MANAGER_H__

#include <vector>

#include "Drawable.h"

class MenuItem : public Drawable {
	protected:
		int x, y;

	public:
		MenuItem(const int & x, const int & y) : x(x), y(y) {}
		virtual void draw(std::shared_ptr<GraphicsEngine>) = 0;
		int getX() const { return x; }
		int getY() const { return y; }
};

class MenuButton : public MenuItem {
	private:
		void(*func)(void);

	public:
		MenuButton(const int & x, const int & y, void(*func)(void)) : MenuItem(x, y), func(func) {}
		virtual void draw(std::shared_ptr<GraphicsEngine>);
		void click() { func(); }
};

class MenuText : public MenuItem {
	private:
		std::string text;

	public:
		MenuText(const int & x, const int & y, std::string & text) : MenuItem(x, y), text(text) {}
		virtual void draw(std::shared_ptr<GraphicsEngine>);
};

class MenuManager : public Drawable {
	private:
		std::vector<std::shared_ptr<MenuButton> > buttons;
		std::vector<std::shared_ptr<MenuText> > texts;

	public:
		void addButton(std::shared_ptr<MenuButton> btn) { buttons.push_back(btn); }
		void addText(std::shared_ptr<MenuText> text) { texts.push_back(text); }
		void draw(std::shared_ptr<GraphicsEngine> gfx) {
			for (auto btn : buttons)
				btn->draw(gfx);
			for (auto t : texts)
				t->draw(gfx);
		}

		void handleClick(const Point2 & pos) {
			for (auto btn : buttons) {
				Rectangle2 r = { btn->getX(), btn->getY(), 200, 50 };
				if (r.contains(pos)) {
					btn->click();
					break;
				}
			}
		}
};

#endif