#include "EventEngine.h"

EventEngine::EventEngine() : running(true)/*, remoteEventEnabled(false)*/ {
	for (int i = 0; i < Key::LAST; ++i) {
		keys[i] = false;
		repeats[i] = false;
	}

	buttons[Mouse::BTN_LEFT] = false;
	buttons[Mouse::BTN_RIGHT] = false;
	/*
#ifdef __DEBUG
	debug("Remote Control is", remoteEventEnabled ? "ON" : "OFF");
#endif

	if (remoteEventEnabled) {
		bool netOK = true, ipOK = true;

		if (SDLNet_Init() < 0) {
			netOK = false;
#ifdef __DEBUG
			debug("Failed to init SDL_net", SDLNet_GetError());
#endif
		}

		if (!netOK || SDLNet_ResolveHost(&ip, NULL, PORT) < 0) {
			ipOK = false;
#ifdef __DEBUG
			debug("Failed to resolve host", SDLNet_GetError());
			debug("Port:", PORT);
#endif
		}

		if (netOK && ipOK) {
			server = SDLNet_TCP_Open(&ip);
			if (server != nullptr) {
				connThread = new std::thread(&EventEngine::runConnThread, this);
#ifdef __DEBUG
				debug("EventEngine::remoteEventEnabled successful");
#endif
			}
			else {
				debug("Failed to create local server", SDLNet_GetError());
			}
		}
	}*/
}

EventEngine::~EventEngine() {
#ifdef __DEBUG
	debug("EventEngine::~EventEngine() started");
#endif
	/*if (remoteEventEnabled) {
		running = false;

		if (connThread)
			connThread->join();	// wait till it finishes

		if (client != nullptr)
			SDLNet_TCP_Close(client);
		if (server != nullptr)
			SDLNet_TCP_Close(server);

		safeDelete(connThread);
		SDLNet_Quit();
	}*/
#ifdef __DEBUG
	debug("EventEngine::~EventEngine() finished");
#endif
}

void EventEngine::runConnThread() {
#ifdef __DEBUG
	debug("EventEngine::runConnThread() started on a separate thread");
#endif

	/*while (running) {
		if (nullptr == client) {
			client = SDLNet_TCP_Accept(server);
		}
		else {
			remoteip = SDLNet_TCP_GetPeerAddress(client);	// TODO: do init once and redo on connection lost
			ipaddr = SDL_SwapBE32(remoteip->host);
			len = SDLNet_TCP_Recv(client, message, 8);	// doesn't return until catches a tcp packet

			for (int i = 0; i < len; ++i) {
				char c = (int)message[i];
			
				keys[Key::W] = ('W' == c && !keys[Key::W]);
				keys[Key::S] = ('S' == c && !keys[Key::S]);
				keys[Key::A] = ('A' == c && !keys[Key::A]);
				keys[Key::D] = ('D' == c && !keys[Key::D]);
				keys[Key::LEFT]  = ('L' == c && !keys[Key::LEFT]);
				keys[Key::RIGHT] = ('R' == c && !keys[Key::RIGHT]);


				if ('N' == c) {
					for (int i = 0; i < Key::LAST; ++i)
						keys[i] = false;
				}
			}
		}
		SDL_Delay(16);
	}*/

#ifdef __DEBUG
	debug("EventEngine::runConnThread() finished on a separate thread");
#endif
}

void EventEngine::pollEvents() {
	while (!keys[QUIT] && SDL_WaitEvent(&event)) {
		if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0) {
			updateKeys(event.key.keysym.sym, event.type == SDL_KEYDOWN);
		}

		if (event.type == SDL_QUIT) {
			keys[QUIT] = true;
		}

		buttons[Mouse::BTN_LEFT]  = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
		buttons[Mouse::BTN_RIGHT] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;

		if (!buttons[Mouse::BTN_LEFT]) repeatsMouse[Mouse::BTN_LEFT] = false;
		if (!buttons[Mouse::BTN_RIGHT]) repeatsMouse[Mouse::BTN_RIGHT] = false;
	}
}

void EventEngine::updateKeys(const SDL_Keycode &key, bool keyDown) {
	Key index;

	switch (key) {
		case SDLK_RIGHT:	index = Key::RIGHT; break;
		case SDLK_d:		index = Key::D; break;
		case SDLK_LEFT:		index = Key::LEFT; break; 
		case SDLK_a:		index = Key::A; break;
		case SDLK_UP:		index = Key::UP; break;
		case SDLK_w:		index = Key::W; break;
		case SDLK_DOWN:		index = Key::DOWN; break;
		case SDLK_s:		index = Key::S; break;
		case SDLK_ESCAPE:	index = Key::ESC; break;
		case SDLK_SPACE:	index = Key::SPACE; break;
		default:
			return;	// we don't care about other keys, at least now
	}

	keys[index] = keyDown;

	if (!keyDown) {
		repeats[index] = false;
	}
}

void EventEngine::setPressed(Key key) {
    keys[key] = true;
}

void EventEngine::setPressed(Mouse btn) {
    buttons[btn] = true;
}

bool EventEngine::isPressed(Key key) {
	return keys[key];
}

bool EventEngine::isPressed(Mouse btn) {
	return buttons[btn];
}

bool EventEngine::isTapped(Key key) {
	if (keys[key] && !repeats[key]) {
		repeats[key] = true;
		return true;
	}

	return false;
}

bool EventEngine::isTapped(Mouse btn) {
	if (buttons[btn] && !repeatsMouse[btn]) {
		repeatsMouse[btn] = true;
		return true;
	}

	return false;
}

void EventEngine::setMouseRelative(bool b) {
	if (SDL_SetRelativeMouseMode(b ? SDL_TRUE : SDL_FALSE) < 0) {
#ifdef __DEBUG
		debug("Warning: SDL_SetRelativeMouseMode() isn't supported");
#endif
	}
}

Point2 EventEngine::getMouseDPos() {
	Point2 mouseDPos;
	SDL_GetRelativeMouseState(&mouseDPos.x, &mouseDPos.y);
	return mouseDPos;
}

Point2 EventEngine::getMousePos() {
	Point2 pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}
