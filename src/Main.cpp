#include "Window/AppWindow.h"

int main()
{
	//AstroidGameMode Game(960, 640, "Astroids");
	Apex::AppWindow app;
	if (app.Init())
	{
		while (app.IsRun())
		{
			app.Broadcast();
		}
	}

	return 0;
}