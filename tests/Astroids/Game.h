#pragma once

#include "Ship.h"
#include "Astroid.h"
#include "Bullet.h"
#include "../src/Window/Window.h"
#include "../src/Graphics/Renderer.h"
#include "../src/Core/Time.h"
#include "../src/Physics/2D/Disc2D.h"

#include <vector>

class Game
{
	Apex::Window g_App;
	Apex::Time g_TS;
	Apex::Renderer* g_Renderer;
	Apex::Disc2D* g_PlayerDisc, * g_AstroidDisc;
	Apex::Ship* g_Player;

	std::vector<Apex::Astroid> g_Astroids;

	Apex::Bullet* g_Bullet;

	Apex::Vec2 g_Update, g_Translate;
	Apex::Vec2 g_BulletVelocity, g_BulletAccelaration;

	bool g_IsFiring;
public:
	Game();
	~Game();

	void SpawnBullets();

	void BeginPlay();
	void Tick();
};