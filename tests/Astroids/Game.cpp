#include "Game.h"

#include "../src/Maths/Random.h"
#include "../src/Core/DebugSystem.h"

Game::Game()
	:g_TS(60), g_Renderer(nullptr), g_Player(nullptr), g_PlayerDisc(nullptr), g_AstroidDisc(nullptr)
{
}

Game::~Game()
{
}

void Game::BeginPlay()
{
	g_TS.SetSeed();
	
	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 
	
	g_Player = new Apex::Ship((Apex::Vec2(30.0f, 30.0f)));
		
	for (int i = 0; i < 0; i++)
	{
		Apex::Astroid g_Object(Apex::Vec2(Apex::Random::GetRandomFloatInRange(75.0f, 275.0f), Apex::Random::GetRandomFloatInRange(175.0f, 375.0f)), i);
	
		g_Astroids.push_back(g_Object);
	}
}

void Game::Tick()
{
	if (g_App.Init())
	{
		//--------------------------------------------------------------------------------------------------
		//GAME LOOP
	
		while (g_App.IsRun())
		{
			g_App.Broadcast();

			g_TS.Update();

			//----------------------------------------------------------------------------------------------
			//Initializing the renderer

			g_Renderer->InitRender();

			//----------------------------------------------------------------------------------------------
			//Rendering the player

				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

			g_PlayerDisc = new Apex::Disc2D(g_Player->GetPosition() + g_Player->GetTranslate(), 15.0f);

			g_Renderer->Push();

			g_Player->OnUpdate(g_TS.GetTimeDelta());

			g_Player->Render();

			Apex::ShipFlames::RenderRight();
			Apex::ShipFlames::RenderLeft();
			Apex::ShipFlames::Render();

			Apex::DebugSystem::DebugCircle(g_PlayerDisc->GetRadius());
			Apex::DebugSystem::DebugLine();

			g_Renderer->Pop();

			//----------------------------------------------------------------------------------------------
			//Rendering the astroids

			for (uint32_t i = 0; i < g_Astroids.size(); i++)
			{
				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

				g_AstroidDisc = new Apex::Disc2D(g_Astroids[i].GetPostion() + g_Astroids[i].GetTranslate(), 55.0f);

				g_Renderer->Push();

				g_Astroids[i].OnUpdate(g_TS.GetTimeDelta());

				g_Astroids[i].Render();

				Apex::DebugSystem::DebugCircle(g_AstroidDisc->GetRadius());

				g_Renderer->Pop();

				//------------------------------------------------------------------------------------------
				//Collision Detection

				if (Apex::Disc2D::CheckCollision(g_AstroidDisc, g_PlayerDisc))
				{
					delete g_Player;
					g_Player = new Apex::Ship((Apex::Vec2(30.0f, 30.0f)));
				}

				//------------------------------------------------------------------------------------------
				//Deleting Heap Allocated Memory

				delete g_AstroidDisc;
			}

			//----------------------------------------------------------------------------------------------
			/*Guarantee that all OpenGL commands
			made up to that point will complete
			executions in a finite amount time*/

			g_Renderer->Flush();

			//----------------------------------------------------------------------------------------------
			//Deleting Heap Allocated Memory

			delete g_PlayerDisc;

			//----------------------------------------------------------------------------------------------
			//Swapping front and back buffers each frame

			g_App.SwappingBuffers();
		}
	}
}