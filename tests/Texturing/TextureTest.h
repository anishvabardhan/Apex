#pragma once

#include "../Window/Window.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Buffers/FrameBuffer.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

class TextureTest
{
	Apex::Window g_App;
	Apex::Renderer g_Renderer;
	Apex::FrameBuffer* g_FrameBuffer;
public:
	TextureTest();
	~TextureTest();

	void Init();
};