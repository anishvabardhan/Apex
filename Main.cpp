#include "../../tests/Texturing/Code/TextureTest.h"
#include "../../tests/Astroids/Code/Game.h"
#include "../Core/EngineUtils.h"

#define ASTROIDS 0

int main()
{
	Apex::EngineStartup();

#if ASTROIDS
	Game* Astroids = new Game();

	Astroids->BeginPlay();

	Astroids->Tick();

	delete Astroids;
#else
	TextureTest* Test = new TextureTest();

	Test->Init();

	delete Test;
#endif

	Apex::EngineShutdown();

	return 0;
}