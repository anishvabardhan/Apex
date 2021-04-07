#include "Window/Window.h"
#include "Graphics/Renderer.h"

#include <gl/GL.h>

int main()
{
	Apex::Window app;
	Apex::Renderer* renderer = nullptr;

	if (app.Init())
	{
		while (app.IsRun())
		{
			app.Broadcast();

			renderer->MainRender();

			SwapBuffers(app.GetDeviceContext());
		}
	}

	return 0;
}