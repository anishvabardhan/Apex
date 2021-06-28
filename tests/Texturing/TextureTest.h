#pragma once

#include "Window/Window.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

class TextureTest
{
	Apex::Window g_App;
public:
	TextureTest();
	~TextureTest();

	void Init();
};