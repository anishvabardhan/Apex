#pragma once

#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"

#include "Physics/2D/Collision2D.h"

#include "Maths/Mat4.h"

class Snake
{
	Apex::Renderable2D* a_Head;
	std::vector<Apex::Renderable2D&> a_Walls;
	Apex::Window* a_Window;
public:

	void CreateHead();
	void CreateWorld();
	void CreateWindow();
};