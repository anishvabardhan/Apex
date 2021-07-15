#pragma once

#include "../Window/Window.h"
#include "../Graphics/FrameBuffer.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

class TextureTest
{
	Apex::Window g_App;
	Apex::FrameBuffer* g_FrameBuffer;
public:
	TextureTest();
	~TextureTest();

	void Init();
};