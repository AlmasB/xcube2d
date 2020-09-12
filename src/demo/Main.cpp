#include "MyGame.h"

int main(int argc, char * args[]) {

	try {
        MyGame game;
		game.runMainLoop();
	} catch (EngineException & e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	return 0;
}