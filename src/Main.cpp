#include "Window/Window.h"
#include "Graphics/Renderer.h"
#include "../tests/Astroids/Ship.h"
#include "../tests/Astroids/Astroid.h"
#include "Input/Input.h"

#include <gl/GL.h>

int main()
{
	//------------------------------------------------------------------------------------------------------
	//Instantiating a window class

	Apex::Window app;
	
	//------------------------------------------------------------------------------------------------------
	//Instantiating a renderer

	Apex::Renderer* renderer = nullptr;
	
	//------------------------------------------------------------------------------------------------------
    //Instatntiating a player 

	Apex::Ship m_Player(Apex::Vec2(512.0f, 384.0f));
	
	//------------------------------------------------------------------------------------------------------
    //Variables

	float angle = 0.0f, x = 0.0f, y = 0.0f;

	//------------------------------------------------------------------------------------------------------
    //Initializing the window

	if (app.Init())
	{   
		//--------------------------------------------------------------------------------------------------
		//GAME LOOP

		while (app.IsRun())
		{
			app.Broadcast();
			//----------------------------------------------------------------------------------------------
            //Initializing the renderer

			renderer->InitRender();
			//----------------------------------------------------------------------------------------------
			//Creating Inputs for the player controller

			if (app.GetKey[RIGHT_ARROW])
			{
				angle -= 0.1f;
			}

			if (app.GetKey[LEFT_ARROW])
			{
				angle += 0.1f;
			}

			if (app.GetKey[D])
			{
				x += 0.1f;
			}
			else if (app.GetKey[A])
			{
				x -= 0.1f;
			}

			if (app.GetKey[W])
			{
				y += 0.1f;
			}
			else if (app.GetKey[S])
			{
				y -= 0.1f;
			}
			//----------------------------------------------------------------------------------------------

			//----------------------------------------------------------------------------------------------
			//Rendering the player

			m_Player.Translation(x, y);
			m_Player.Rotation(angle);
			renderer->Begin();
			m_Player.Render();
			renderer->End();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			SwapBuffers(app.GetDeviceContext());
		}
	}

	return 0;
}