#include <ctime>
#include "Game.h"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	Game myGame;

	while(myGame.IsRunning())
	{
		myGame.Update();
		myGame.Render();
	}

	return 0;
}
