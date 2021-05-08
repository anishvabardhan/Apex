#include "../tests/Astroids/Game.h"

int main()
{
	Game* Astroids = new Game();

	Astroids->BeginPlay();

	Astroids->Tick();

	delete Astroids;

	return 0;
}