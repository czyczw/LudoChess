#include "FlyGame.h"

int main()
{
	srand(time(NULL));
	Game FlyGame;
	while (FlyGame.window.isOpen())
	{
		FlyGame.Run();
	}
	return 0;
}