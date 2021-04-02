#pragma once

#include <Windows.h>
#include <GL/GL.h>

namespace Apex {

	class Window
	{
	public:
		Window();
		~Window();

		bool Init();
		bool Broadcast();
		bool Release();
		bool IsRun();

		virtual void OnCreate(HWND hwnd);
		virtual void OnUpdate();
		virtual void OnDestroy();
	protected:
		HWND m_Hwnd;
		bool m_IsRun;
	};

}