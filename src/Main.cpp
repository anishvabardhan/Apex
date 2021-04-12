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

	Apex::Window g_App;
	
	//------------------------------------------------------------------------------------------------------
	//Instantiating a renderer

	Apex::Renderer* g_Renderer = nullptr;
	
	//------------------------------------------------------------------------------------------------------
    //Instatntiating a player 

	Apex::Ship g_Player(Apex::Vec2(512.0f, 384.0f));
	Apex::Astroid g_Object(Apex::Vec2(612.0f, 384.0f));
	
	//------------------------------------------------------------------------------------------------------
    //Variables

	float p_Angle = 0.0f, o_Angle = 0.0f, x = 0.0f, y = 0.0f;

	//------------------------------------------------------------------------------------------------------
    //Initializing the window

	if (g_App.Init())
	{   
		//--------------------------------------------------------------------------------------------------
		//GAME LOOP

		while (g_App.IsRun())
		{
			g_App.Broadcast();

			//----------------------------------------------------------------------------------------------
            //Initializing the renderer

			g_Renderer->InitRender();

			//----------------------------------------------------------------------------------------------
			//Creating Inputs for the player controller

			if (g_App.GetKey[RIGHT_ARROW])
			{
				p_Angle -= 0.1f;
			}

			if (g_App.GetKey[LEFT_ARROW])
			{
				p_Angle += 0.1f;
			}

			if (g_App.GetKey[D])
			{
				x += 0.1f;
			}
			else if (g_App.GetKey[A])
			{
				x -= 0.1f;
			}

			if (g_App.GetKey[W])
			{
				y += 0.1f;
			}
			else if (g_App.GetKey[S])
			{
				y -= 0.1f;
			}
			//----------------------------------------------------------------------------------------------

			o_Angle += 0.075f;

			//----------------------------------------------------------------------------------------------
			//Rendering the player

			g_Player.Translation(x, y);
			g_Player.Rotation(p_Angle);

			g_Renderer->Begin();

			g_Player.Render();

			g_Renderer->End();

			//----------------------------------------------------------------------------------------------
			//Rendering the object

			g_Object.Translation();
			g_Object.Rotation(o_Angle);

			g_Renderer->Begin();

			g_Object.Render();

			g_Renderer->End();

			glFlush();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			SwapBuffers(g_App.GetDeviceContext());
		}
	}

	return 0;
}