#include "Game.h"

#include "../src/Maths/Random.h"
#include "../src/Core/DebugSystem.h"

Game::Game()
	:g_TS(60), g_BulletVelocity(Apex::Vec2(7.5f, 7.5f)), g_Renderer(nullptr), g_Player(nullptr), g_Objects(nullptr), g_PlayerDisc(nullptr), g_NumOfBullets(0), g_NumOfAstroids(8), g_BulletLife(50.0f), g_IsFiring(false)
{
	for (int i = 0; i < g_NumOfAstroids; i++)
	{
		g_Astroid[i] = nullptr;
		g_AstroidDisc[i] = nullptr;
	}

	g_Bullet = nullptr;
}

Game::~Game()
{
	delete g_Player;
	delete g_Renderer;
}

void Game::BeginPlay()
{
	g_TS.SetSeed();
	
	//------------------------------------------------------------------------------------------------------
	//Instatntiating the characters 
	
	g_Player = new Apex::Ship((Apex::Vec2(30.0f, 30.0f)));

	g_Bullet = new Apex::Bullet(g_Translate);

	for (int i = 0; i < g_NumOfAstroids; i++)
	{	
		g_Objects = new Apex::Astroid(Apex::Vec2(Apex::Random::GetRandomFloatInRange(75.0f, 275.0f), Apex::Random::GetRandomFloatInRange(175.0f, 375.0f)), i);

		g_Astroid[i] = g_Objects;

		g_AstroidDisc[i] = new Apex::Disc2D(g_Astroid[i]->GetPostion() + g_Astroid[i]->GetTranslate(), g_Astroid[i]->GetRadius());
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

			if (g_Bullet != nullptr)
			{
				g_BulletDisc = new Apex::Disc2D(g_Bullet->GetPosition() + g_Update, g_Bullet->m_Radius);
			}
			g_Renderer->Push();

			if (g_App.GetKey[SPACEBAR])
			{
				SpawnBullet();
			}

			if (g_IsFiring)
			{
				g_Update += g_BulletVelocity;

				g_Bullet->OnUpdate(g_Update, g_TS.GetTimeDelta());

				g_Bullet->Render();
			}
			else
			{
				g_Translate = g_Player->GetPosition() + g_Player->GetNosePosition() + g_Player->GetTranslate();
			}

			if (g_Bullet != nullptr && g_Bullet->GetAge() > g_BulletLife)
			{
				DestroyBullet();
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

			for (int i = 0; i < g_NumOfAstroids; i++)
			{
				//------------------------------------------------------------------------------------------
				//Applying the collision discs on the entity

				if (g_Astroid[i] != nullptr && g_AstroidDisc[i] != nullptr)
				{
					g_AstroidDisc[i] = new Apex::Disc2D(g_Astroid[i]->GetPostion() + g_Astroid[i]->GetTranslate(), g_Astroid[i]->GetRadius());


					g_Renderer->Push();

					g_Astroid[i]->OnUpdate(g_TS.GetTimeDelta());

					g_Astroid[i]->Render();

					Apex::DebugSystem::DebugCircle(g_AstroidDisc[i]->GetRadius());

					g_Renderer->Pop();

					//------------------------------------------------------------------------------------------
					//Collision Detection

					if (Apex::Disc2D::CheckCollision(g_AstroidDisc[i], g_PlayerDisc))
					{
						delete g_Player;
						g_Player = new Apex::Ship((Apex::Vec2(30.0f, 30.0f)));
					}

					for (int i = 0; i < g_NumOfAstroids; i++)
					{
						if (g_Bullet != nullptr && g_Astroid[i] != nullptr && g_AstroidDisc[i] != nullptr)
						{
							if (Apex::Disc2D::CheckCollision(g_BulletDisc, g_AstroidDisc[i]))
							{
								DestroyAstroid(i);
								DestroyBullet();
							}
						}
					}

					//------------------------------------------------------------------------------------------
					//Deleting Heap Allocated Memory
				}
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

void Game::SpawnBullet()
{
	g_IsFiring = true;

	Apex::Vec2 forwardDir = g_Player->GetNosePosition().GetNormalised();

	g_BulletVelocity = Apex::Vec2(6.5f, 6.5f);

	g_BulletVelocity *= forwardDir * g_TS.GetTimeDelta();

	g_Bullet = new Apex::Bullet(g_Translate);
}

void Game::DestroyBullet()
{
	delete g_Bullet;
	g_Bullet = nullptr;
	g_Update = Apex::Vec2(0.0f, 0.0f);
	g_IsFiring = false;
}

void Game::DestroyAstroid(int index)
{
	if (index == g_NumOfAstroids - 1)
	{
		delete (g_Astroid[index]);
		delete g_AstroidDisc[index];
		g_Astroid[index] = nullptr;
		g_AstroidDisc[index] = nullptr;
	}
	else
	{
		delete(g_Astroid[index]);
		g_Astroid[index] = nullptr;
		for (int j = index + 1; g_Astroid[j] != nullptr; j++)
		{
			g_Astroid[j - 1] = g_Astroid[j];
			g_Astroid[j] = nullptr;
		}

		delete(g_AstroidDisc[index]);
		g_AstroidDisc[index] = nullptr;
		for (int j = index + 1; g_AstroidDisc[j] != nullptr; j++)
		{
			g_AstroidDisc[j - 1] = g_AstroidDisc[j];
			g_AstroidDisc[j] = nullptr;
		}

	}
}
