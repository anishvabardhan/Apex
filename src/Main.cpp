#include "Window/Window.h"

int main()
{
	Apex::Window app;

	if (app.Init())
	{
		while (app.IsRun())
		{
			app.Broadcast();

			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

			SwapBuffers(app.GetDeviceContext());
		}
	}

	return 0;
}