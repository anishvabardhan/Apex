#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

namespace Apex {

	class AppWindow
	{
		int m_Width;
		int m_Height;

		HWND m_Window;
	public:
		explicit AppWindow(int width, int height);
		~AppWindow();

		int Init();
		void Clear() const;
		bool Close() const;
		void SetClose() const;
		void Update() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
	};

}