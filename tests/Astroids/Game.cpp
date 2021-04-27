#include "Game.h"

#include "Window/Window.h"
#include "Graphics/Renderer.h"
#include "../tests/Astroids/Ship.h"
#include "../tests/Astroids/Astroid.h"
#include "Input/Input.h"

#include <vector>

Game::Game()
{
}

Game::~Game()
{
}

void Game::BeginPlay()
{
	srand((unsigned int)time(0));

	//------------------------------------------------------------------------------------------------------
	//Instantiating a window class

	Apex::Window g_App;

	//------------------------------------------------------------------------------------------------------
	//Instantiating a renderer

	Apex::Renderer* g_Renderer = nullptr;

	//------------------------------------------------------------------------------------------------------
	//Variables

	int x = 0;
	float p_Angle = 0.0f, o_Angle = 0.0f, p_X = 0.0f, p_Y = 0.0f, o_X = (float)(rand() % 300), o_Y = (float)(rand() % 300), a_X = 0.0095f, a_Y = 0.0095f;
	bool c_X[8], c_Y[8];

	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 

	Apex::Ship g_Player(Apex::Vec2(30.0f, 30.0f));

	std::vector<Apex::Astroid> g_Astroid;
	std::vector<Apex::Vec2> g_Translate, g_Update;

	for (int i = 0; i < 8; i++)
	{
		Apex::Astroid g_Object(Apex::Vec2((float)(rand() % 600), (float)(rand() % 400)));

		g_Astroid.push_back(g_Object);
		g_Translate.push_back(Apex::Vec2(o_X, o_Y));
		g_Update.push_back(Apex::Vec2(a_X * (i + 1), a_Y * (i + 1)));
	}

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
			//Updating the values every frame
			
			for(uint32_t i = 0; i < g_Translate.size(); i++)
			{
				g_Translate[i].m_X += g_Update[i].m_X;
				g_Translate[i].m_Y += g_Update[i].m_Y;
			}

			o_Angle += 0.075f;
			
			//----------------------------------------------------------------------------------------------
			//Collision Detection between player and astroids

			for (int i = 0; i < 8; i++)
			{
				c_X[i] = ((g_Astroid[i].GetPostion().m_X + g_Translate[i].m_X + 56.0f >= g_Player.GetPosition().m_X + p_X) && (g_Astroid[i].GetPostion().m_X + g_Translate[i].m_X - 56.0f <= g_Player.GetPosition().m_X + p_X));

				c_Y[i] = ((g_Astroid[i].GetPostion().m_Y + g_Translate[i].m_Y + 56.0f >= g_Player.GetPosition().m_Y + p_Y) && (g_Astroid[i].GetPostion().m_Y + g_Translate[i].m_Y - 56.0f <= g_Player.GetPosition().m_Y + p_Y));

				if (c_X[i] && c_Y[i])
				{
					x++;
				}
			}

			//----------------------------------------------------------------------------------------------
			//Game Over if collision detected

			if (x != 0)
			{
				g_App.Release();
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
			//Rendering the astroids

			for(int i = 0; i < 8; i++)
			{
				g_Astroid[i].Translation(g_Translate[i].m_X, g_Translate[i].m_Y);
				g_Astroid[i].Rotation(o_Angle);

				g_Renderer->BeginLine();

				g_Astroid[i].Render();

				g_Renderer->End();

				if (g_Astroid[i].GetPostion().m_Y + g_Translate[i].m_Y + 100.0f >= 768.0f || g_Astroid[i].GetPostion().m_Y + g_Translate[i].m_Y - 60.0f <= 0.0f)
				{
					g_Update[i].m_Y = -g_Update[i].m_Y;
				}

				if (g_Astroid[i].GetPostion().m_X + g_Translate[i].m_X + 67.5f >= 1024.0f || g_Astroid[i].GetPostion().m_X + g_Translate[i].m_X - 47.5f <= 0.0f)
				{
					g_Update[i].m_X = -g_Update[i].m_X;
				}
			}

			//----------------------------------------------------------------------------------------------
			/*Guarantee that all OpenGL commands 
			made up to that point will complete 
			executions in a finite amount time*/

			g_Renderer->Flush();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();
		}
	}
}