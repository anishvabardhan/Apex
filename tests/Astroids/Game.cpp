#include "Game.h"

#include "../src/Window/Window.h"
#include "../src/Graphics/Renderer.h"
#include "../src/Core/Time.h"
#include "../src/Input/Input.h"
#include "../src/Physics/2D/Disc2D.h"

#include "Ship.h"
#include "Astroid.h"

#include <vector>

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
	//Locking FPS
	Apex::Time g_TS(60);
	g_TS.SetSeed();

	//------------------------------------------------------------------------------------------------------
	//Instantiating a renderer

	Apex::Renderer* g_Renderer = nullptr;
	Apex::Disc2D *g_PlayerDisc, *g_AstroidDisc;

	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 

	Apex::Ship g_Player(Apex::Vec2(30.0f, 30.0f));

	float g_Dist1 = 65.0f;
	int x = 0;

	std::vector<Apex::Astroid> g_Astroids;

	for (int i = 0; i < 8; i++)
	{
		Apex::Astroid g_Object(Apex::Vec2((float)(rand() % 200) + 75.0f, (float)(rand() % 200) + 75.0f), i);

		g_Astroids.push_back(g_Object);
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
				g_PlayerDisc = new Apex::Disc2D(g_Player.GetPosition() + g_Player.GetTranslate(), 15.0f);

				g_Renderer->Push();

				g_Player.OnUpdate(g_TS.GetDeltaTime());

				g_Renderer->BeginLine();

				g_Player.Render();

				g_Renderer->End();

				g_Renderer->Pop();
			}

			//----------------------------------------------------------------------------------------------
			//Rendering the astroids

			for (uint32_t i = 0; i < g_Astroids.size(); i++)
			{
				g_AstroidDisc = new Apex::Disc2D(g_Astroids[i].GetPostion() + g_Astroids[i].GetTranslate(), 50.0f);

				g_Renderer->Push();

				g_Astroids[i].OnUpdate(g_TS.GetDeltaTime());

				g_Renderer->BeginLine();

				g_Astroids[i].Render();

				g_Renderer->End();

				g_Renderer->Pop();

				if (Apex::Disc2D::CheckCollision(g_AstroidDisc, g_PlayerDisc))
				{
					x++;
				}

				delete g_AstroidDisc;
			}
			
			if (x > 0)
			{
				g_App.Release();
			}

			//----------------------------------------------------------------------------------------------
			/*Guarantee that all OpenGL commands 
			made up to that point will complete 
			executions in a finite amount time*/

			g_Renderer->Flush();

			delete g_PlayerDisc;

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();

			g_TS.End();
		}
	}
}