#pragma once

#include "Graphics/Renderer.h"
#include "Window/Window.h"

class TextureTest
{
	Apex::Window g_App;
	Apex::Renderer* g_Renderer;
public:
	TextureTest();
	~TextureTest();

	void Init();
};