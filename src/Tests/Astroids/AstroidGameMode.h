#pragma once

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/OrthoGraphic.h"
#include "Graphics/Renderable2D.h"

#include "Physics/2D/Collision2D.h"

#include "Maths/Maths.h"

#include "Astroid.h"
#include "Player.h"

#define MAX_ASTROIDS 4

class AstroidGameMode
{
	int g_Width, g_Height;
	std::string g_Title;
	Apex::Window* g_Window;
	Apex::Shader g_Shader;
public:
	explicit AstroidGameMode(int width, int height, std::string title);
	~AstroidGameMode();

	void CreateGame();

	Apex::Shader& CreateShader(const std::string& filepath);
};