#ifndef __EVENT_ENGINE_H__
#define __EVENT_ENGINE_H__

#include <string>
#include <thread>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_net.h>

#include "../core/EngineCommon.h"
#include "../math/GameMath.h"

enum Key {
	W, S, A, D, ESC, SPACE, UP, DOWN, LEFT, RIGHT, QUIT, LAST
};

enum Mouse {
	BTN_LEFT, BTN_RIGHT, BTN_LAST
};

//static const Uint16 PORT = 55555;	// should be safe

class EventEngine {
	friend class XCube2Engine;
	private:
		bool running;
		SDL_Event event;

		bool keys[Key::LAST];
		bool repeats[Key::LAST];

		bool buttons[Mouse::BTN_LAST];
		bool repeatsMouse[Mouse::BTN_LAST];

		void updateKeys(const SDL_Keycode &, bool);

		/*bool remoteEventEnabled;
		std::thread * connThread;

		IPaddress ip, *remoteip;
		TCPsocket server, client;
		char message[8];	// recv buffer;
		int len;
		Uint32 ipaddr;
		Uint16 port;*/

		EventEngine();
	public:
		~EventEngine();

		/**
		* Push SDL_QUIT event to stop
		* waitAndDispatchEvents()
		*
		* This allows to call stop even when
		* the user didn't close the window
		* e.g. user hit EXIT from the game menu
		*/
		void pushQuitEvent();

		/**
		* this will block execution and keep
		* dispatching events until
		* SDL_QUIT has occurred (user closed application window)
		* OR
		* pushQuitEvent() has been called
		*/
		void waitAndDispatchEvents();

		/**
		* @return true only once per actual physical press/click
		*/
		bool isTapped(Key);
		bool isTapped(Mouse);
		
		bool isPressed(Key);
		bool isPressed(Mouse);
    
        /**
         * Software emulation of keypresses
         */
        void setPressed(Key);
        void setPressed(Mouse);
	
		void setMouseRelative(bool);

		/**
		* Returns mouse's delta position
		* It's the difference between current and
		* previous mouse positions
		*
		*/
		Point2 getMouseDPos();

		/**
		* Returns current mouse position relative to the window
		*/
		Point2 getMousePos();

		/**
		* Starts executing android "joystick" listener
		* on a separate thread
		*/
		void runConnThread();
};

#endif
