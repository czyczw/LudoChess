#include "FlyGame.h"

int main()
{
	Game FlyGame;
	while (FlyGame.window.isOpen())
	{
		FlyGame.Run();
	}
	return 0;
}