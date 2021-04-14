#include "Window/Window.h"
#include "Graphics/Renderer.h"
#include "../tests/Astroids/Ship.h"
#include "../tests/Astroids/Astroid.h"
#include "../tests/Astroids/Bullet.h"
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

	Apex::Ship g_Player(Apex::Vec3(512.0f, 384.0f, 0.0f));
	Apex::Astroid g_Object(Apex::Vec2(312.0f, 384.0f));
	Apex::Bullet g_Bullet(g_Player.GetPosition() + g_Player.GetNosePosition());
	
	//------------------------------------------------------------------------------------------------------
    //Variables

	float p_Angle = 0.0f, o_Angle = 0.0f, p_X = 0.0f, p_Y = 0.0f, o_X = 0.0f, o_Y = 0.0f;;

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
				p_X += 0.1f;
			}
			else if (g_App.GetKey[A])
			{
				p_X -= 0.1f;
			}

			if (g_App.GetKey[W])
			{
				p_Y += 0.1f;
			}
			else if (g_App.GetKey[S])
			{
				p_Y -= 0.1f;
			}
			//----------------------------------------------------------------------------------------------

			o_Angle +=   0.025f;
			o_X     -=   0.005f;
			o_Y     -=   0.035f;

			//----------------------------------------------------------------------------------------------
			//Rendering the bullet
			
			g_Bullet.Translation(p_X, p_Y);
			g_Bullet.Rotation(p_Angle);

			g_Renderer->BeginQuads();

			g_Bullet.Render();

			g_Renderer->End();

			//----------------------------------------------------------------------------------------------
			//Rendering the player

			g_Player.Translation(p_X, p_Y);
			g_Player.Rotation(p_Angle);

			g_Renderer->BeginLine();

			g_Player.Render();

			g_Renderer->End();

			//----------------------------------------------------------------------------------------------
			//Rendering the object

			g_Object.Translation(o_X, o_Y);
			g_Object.Rotation(o_Angle);

			g_Renderer->BeginLine();

			g_Object.Render();

			g_Renderer->End();

			//glFlush();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			SwapBuffers(g_App.GetDeviceContext());
		}
	}

	return 0;
}