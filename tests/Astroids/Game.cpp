#include "Game.h"

#include "Window/Window.h"
#include "Graphics/Renderer.h"
#include "../tests/Astroids/Ship.h"
#include "../tests/Astroids/Astroid.h"
#include "Input/Input.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::BeginPlay()
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

	//------------------------------------------------------------------------------------------------------
	//Variables

	float p_Angle = 0.0f, p_X = 0.0f, p_Y = 0.0f, o_X = 0.0f, o_Y = 0.0f, a_X = 0.035f, a_Y = 0.035f;

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

			if (g_App.GetKey[D] && g_Player.GetPosition().m_X + p_X < 984.0f)
			{
				p_X += 0.1f;
			}
			else if (g_App.GetKey[A] && g_Player.GetPosition().m_X + p_X > 20.0f)
			{
				p_X -= 0.1f;
			}

			if (g_App.GetKey[W] && g_Player.GetPosition().m_Y + p_Y < 698.0f)
			{
				p_Y += 0.1f;
			}
			else if (g_App.GetKey[S] && g_Player.GetPosition().m_Y + p_Y > 20.0f)
			{
				p_Y -= 0.1f;
			}

			//----------------------------------------------------------------------------------------------

			o_X += a_X;
			o_Y += a_Y;

			if (g_Object.GetPostion().m_Y + o_Y + 100.0f >= 768.0f || g_Object.GetPostion().m_Y + o_Y - 60.0f <= 0.0f)
			{
				a_Y = -a_Y;
			}

			if (g_Object.GetPostion().m_X + o_X + 67.5f >= 1024.0f || g_Object.GetPostion().m_X + o_X - 47.5f <= 0.0f)
			{
				a_X = -a_X;
			}

			//----------------------------------------------------------------------------------------------
			//Rendering the player
			{
				g_Player.Translation(p_X, p_Y);
				g_Player.Rotation(p_Angle);

				g_Renderer->BeginLine();

				g_Player.Render();

				g_Renderer->End();
			}
			//----------------------------------------------------------------------------------------------
			//Rendering the object
			{
				g_Object.Translation(o_X, o_Y);

				g_Renderer->BeginLine();

				g_Object.Render();

				g_Renderer->End();
			}
			//----------------------------------------------------------------------------------------------

			g_Renderer->Flush();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();
		}
	}
}