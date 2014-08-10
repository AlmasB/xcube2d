#include "TestGame.h"

int main(int argc, char * args[]) {
	{
		std::shared_ptr<TestGame> game = std::shared_ptr<TestGame>(new TestGame());

		try {
			//TestGame game;

			Task t(16, std::shared_ptr<Runnable>(game));
			t.start();

			game->runMainLoop();

			t.cancel();


		}
		catch (EngineException & e) {
			std::cout << e.what() << std::endl;
			getchar();
		}


	}
	getchar();
	return 0;
}