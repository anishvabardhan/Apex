#pragma once

#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"
#include "Graphics/OrthoGraphic.h"

#include "Physics/2D/Collision2D.h"

#include "Maths/Mat4.h"

class BreakOut
{
	int g_Width, g_Height;
	std::string g_Title;
	Apex::Window* g_Window;
public:
	explicit BreakOut(int width, int height, std::string title);
	~BreakOut();

	void Init();

	inline int GetWidth() const { return g_Width; }
	inline int GetHeight() const { return g_Height; }
};