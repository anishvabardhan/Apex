#include <iostream>

#include "Graphics/Window.h"

using namespace Apex;

int main()
{
	Window* window;

	window = new Window("Apex", 640, 480);

	while (!window->Close())
	{
		window->Clear();

		window->Update();
	}
}