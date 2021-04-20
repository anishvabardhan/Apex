#include "Window/Window.h"
#include "Graphics/Renderer.h"
#include "../tests/Astroids/Ship.h"
#include "../tests/Astroids/Astroid.h"
#include "../tests/Astroids/Bullet.h"
#include "Physics/2D/Collision2D.h"
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
    //Instatntiating the characters 

	Apex::Ship g_Player(Apex::Vec2(512.0f, 384.0f));
	Apex::Astroid g_Object(Apex::Vec2(312.0f, 384.0f));
	//Apex::Bullet g_Bullet(g_Player.GetPosition());
	
	//------------------------------------------------------------------------------------------------------
    //Variables

	float p_Angle = 0.0f, o_Angle = 0.0f, p_X = 0.0f, p_Y = 0.0f, o_X = 0.0f, o_Y = 0.0f, b_X = 0.0f, b_Y = 0.0f, a_X = p_X, a_Y = p_Y;

	//------------------------------------------------------------------------------------------------------
    //Initializing the window

	if (g_App.Init())
	{   
		//--------------------------------------------------------------------------------------------------
		//GAME LOOP

		while (g_App.IsRun())
		{
			g_App.Broadcast();

			std::cout << g_Player.GetPosition() + Apex::Vec2(p_X, p_Y) << std::endl;

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

			if (g_App.GetKey[D] && g_Player.GetPosition().m_X + p_X < 984.0f)
			{
				p_X += 0.1f;
				a_X = p_X;
			}
			else if (g_App.GetKey[A] && g_Player.GetPosition().m_X + p_X > 20.0f)
			{
				p_X -= 0.1f;
				a_X = p_X;
			}

			if (g_App.GetKey[W] && g_Player.GetPosition().m_Y + p_Y < 698.0f)
			{
				p_Y += 0.1f;
				a_Y = p_Y;
			}
			else if (g_App.GetKey[S] && g_Player.GetPosition().m_Y + p_Y > 20.0f)
			{
				p_Y -= 0.1f;
				a_Y = p_Y;
			}

			//----------------------------------------------------------------------------------------------

			o_Angle +=   0.025f;
			o_X     +=   0.035f;
			o_Y     +=   0.035f;

			//----------------------------------------------------------------------------------------------
			//Rendering the bullet
			
			//g_Bullet.Translation(a_X, a_Y);
			//g_Bullet.Rotation(p_Angle);
			//g_Bullet.PivotAxis(g_Player.GetNosePosition().m_X, g_Player.GetNosePosition().m_Y);
			//
			//g_Renderer->BeginQuads();
			//
			//g_Bullet.Render();
			//
			//g_Renderer->End();

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

			//----------------------------------------------------------------------------------------------

			g_Renderer->Flush();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();
		}
	}

	return 0;
}