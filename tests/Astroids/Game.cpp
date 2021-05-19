#include "Game.h"

#include "../src/Maths/Random.h"
#include "../src/Core/DebugSystem.h"

#define MAX_ASTROIDS 6
#define MAX_BULLETS 1

Game::Game()
	:g_TS(60), g_Renderer(nullptr), g_Player(nullptr), g_Bullet(nullptr), g_PlayerDisc(nullptr), g_AstroidDisc(nullptr), g_Update{0.0f, 0.0f}, g_BulletVelocity{0.0f, 0.0f}, g_BulletAccelaration{0.0f, 0.0f}, g_IsFiring(false)
{
}

Game::~Game()
{
	delete g_Player;
	delete g_Renderer;
}

void Game::SpawnBullets()
{
}

void Game::BeginPlay()
{
	g_TS.SetSeed();
	
	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 
	
	g_Player = new Apex::Ship((Apex::Vec2(30.0f, 30.0f)));

	for (int i = 0; i < MAX_ASTROIDS; i++)
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

			g_Renderer->Push();

			if (g_App.GetKey[SPACEBAR])
			{
				g_IsFiring = true;
				g_BulletAccelaration = Apex::Vec2(1.5f * g_TS.GetTimeDelta(), 1.5f * g_TS.GetTimeDelta());
			}
			else
			{
				g_BulletAccelaration = Apex::Vec2(0.0f, 0.0f);
			}

			if (g_IsFiring)
			{
				g_Bullet = new Apex::Bullet(g_Translate);

				Apex::Vec2 forwardDir = g_Player->GetNosePosition().GetNormalised();

				g_BulletVelocity += g_BulletAccelaration * forwardDir * g_TS.GetTimeDelta();
				g_Update += g_BulletVelocity;

				g_Bullet->OnUpdate(g_Update, g_Player->GetNosePosition(), g_TS.GetTimeDelta());

				g_Bullet->Render();
			}
			else
			{
				g_Translate = g_Player->GetPosition() + g_Player->GetNosePosition() + g_Player->GetTranslate();
			}

			g_Renderer->Pop();

			//----------------------------------------------------------------------------------------------
			//Rendering the player

				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

			g_PlayerDisc = new Apex::Disc2D(g_Player->GetPosition() + g_Player->GetTranslate(), 15.0f);

			g_Renderer->Push();

			g_Player->OnUpdate(g_TS.GetTimeDelta());

			g_Player->Render();

			Apex::DebugSystem::DebugCircle(g_PlayerDisc->GetRadius());
			Apex::DebugSystem::DebugLine();

			g_Renderer->Pop();

			//----------------------------------------------------------------------------------------------
			//Rendering the astroids

			for (uint32_t i = 0; i < g_Astroids.size(); i++)
			{
				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

				g_AstroidDisc = new Apex::Disc2D(g_Astroids[i].GetPostion() + g_Astroids[i].GetTranslate(), g_Astroids[i].GetRadius());

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