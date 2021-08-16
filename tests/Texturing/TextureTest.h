#pragma once

#include "../External/tinyxml2.h"
#include "../Window/Window.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Buffers/FrameBuffer.h"
#include "../Core/Time.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

class TextureTest
{
	Apex::Window g_App;
	Apex::Time g_Time;
	Apex::Renderer g_Renderer;
	Apex::FrameBuffer* g_CurrentFrameBuffer;
	Apex::FrameBuffer* g_NextFrameBuffer;
public:
	TextureTest();
	~TextureTest();

	void Init();
};