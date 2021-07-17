#pragma once

#include "../Window/Window.h"
#include "../Graphics/Renderer.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

class TextureTest
{
	Apex::Window g_App;
	Apex::Renderer g_Renderer;
public:
	TextureTest();
	~TextureTest();

	void Init();
};