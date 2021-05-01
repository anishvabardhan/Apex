#include "Game.h"

#include "Window/Window.h"
#include "Graphics/Renderer.h"
#include "../tests/Astroids/Ship.h"
#include "../tests/Astroids/Astroid.h"
#include "../src/Core/Time.h"
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
	//Locking FPS
	Apex::Time g_TS(60);

	//------------------------------------------------------------------------------------------------------
	//Instantiating a renderer

	Apex::Renderer* g_Renderer = nullptr;

	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 

	Apex::Ship g_Player(Apex::Vec2(30.0f, 30.0f));

	std::vector<Apex::Astroid> g_Astroid;

	for (int i = 0; i < 1; i++)
	{
		Apex::Astroid g_Object(Apex::Vec2((float)(rand() % 200) + 75.0f, (float)(rand() % 200) + 75.0f), i);

		g_Astroid.push_back(g_Object);
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

			g_TS.Start();

			//----------------------------------------------------------------------------------------------
			//Initializing the renderer

			g_Renderer->InitRender();

			//----------------------------------------------------------------------------------------------
			//Rendering the player

			{
				g_Renderer->Push();

				g_Player.OnUpdate(g_TS.GetDeltaTime());

				g_Renderer->BeginLine();

				g_Player.Render();

				g_Renderer->End();

				g_Renderer->Pop();
			}

			//----------------------------------------------------------------------------------------------
			//Rendering the astroids

			for (uint32_t i = 0; i < g_Astroid.size(); i++)
			{
				g_Renderer->Push();

				g_Astroid[i].OnUpdate(g_TS.GetDeltaTime());

				g_Renderer->BeginLine();

				g_Astroid[i].Render();

				g_Renderer->End();

				g_Renderer->Pop();
			}

			//----------------------------------------------------------------------------------------------
			/*Guarantee that all OpenGL commands 
			made up to that point will complete 
			executions in a finite amount time*/

			g_Renderer->Flush();

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();

			g_TS.End();
		}
	}
}