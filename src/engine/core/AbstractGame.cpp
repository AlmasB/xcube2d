#include "AbstractGame.h"

AbstractGame::AbstractGame() : running(true), paused(false), gameTime(0.0) {
	std::shared_ptr<XCube2Engine> engine = XCube2Engine::getInstance();

	// engine ready, get subsystems
	gfx = engine->getGraphicsEngine();
	sfx = engine->getAudioEngine();
	eventSystem = engine->getEventEngine();
	physics = engine->getPhysicsEngine();
}

AbstractGame::~AbstractGame() {
#ifdef __DEBUG
	debug("AbstractGame::~AbstractGame() started");
#endif

	// kill Game class' instance pointers
	// so that engine is isolated from the outside world
	// before shutting down
	gfx.reset();
	eventSystem.reset();

	// kill engine
	XCube2Engine::quit();

#ifdef __DEBUG
	debug("AbstractGame::~AbstractGame() finished");
	debug("The game finished and cleaned up successfully. Press Enter to exit");
	getchar();
#endif
}

int AbstractGame::runMainLoop() {
#ifdef __DEBUG
	debug("Entered Main Loop");
#endif

	while (running) {
		gfx->setFrameStart();
		eventSystem->pollEvents();

		if (eventSystem->isPressed(Key::ESC) || eventSystem->isPressed(Key::QUIT))
			running = false;

		handleKeyEvents();
		handleMouseEvents();

		if (!paused) {
			update();
			updatePhysics();

			gameTime += 0.016;	// 60 times a sec
		}

		gfx->clearScreen();
		render();
		renderUI();
		gfx->showScreen();

		gfx->adjustFPSDelay(16);	// atm hardcoded to ~60 FPS
	}

#ifdef __DEBUG
	debug("Exited Main Loop");
#endif

	return 0;
}

void AbstractGame::handleMouseEvents() {
	if (eventSystem->isPressed(Mouse::BTN_LEFT)) onLeftMouseButton();
	if (eventSystem->isPressed(Mouse::BTN_RIGHT)) onRightMouseButton();
}

void AbstractGame::updatePhysics() {
	physics->update();
}

void AbstractGame::onLeftMouseButton() {}
void AbstractGame::onRightMouseButton() {}
void AbstractGame::renderUI() {}