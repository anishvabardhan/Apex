#pragma once

#include "Ship.h"
#include "Astroid.h"
#include "Bullet.h"
#include "../Window/Window.h"
#include "../Graphics/Renderer.h"
#include "../Core/Time.h"
#include "../Physics/2D/Disc2D.h"

const int MAX_ASTEROIDS = 150;
const int MAX_BULLETS = 6;

class Game
{
	Apex::Window g_App;
	Apex::Time g_TS;
	Apex::Renderer* g_Renderer;
	Apex::Disc2D *g_PlayerDisc, *g_AstroidDisc[MAX_ASTEROIDS], *g_BulletDisc;
	Apex::Ship* g_Player;

	Apex::Astroid* g_Objects;
	Apex::Astroid* g_Astroid[MAX_ASTEROIDS];

	Apex::Bullet* g_Bullet;

	Apex::Vec2 g_Update;
	Apex::Vec2 g_Translate;
	Apex::Vec2 g_BulletVelocity;

	float g_BulletLife;

	bool g_IsFiring;

	int g_NumOfBullets;
	int g_NumOfAstroids;
public:
	Game();
	~Game();

	void BeginPlay();
	void Tick();

	void SpawnBullet();
	void DestroyBullet();

	void DestroyAstroid(int index);
};