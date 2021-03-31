#include "Window/Window.h"

int main()
{
	Apex::Window app;

	if (app.Init())
	{
		while (app.IsRun())
		{
			app.Broadcast();
		}
	}

	return 0;
}