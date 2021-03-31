#pragma once

#include <Windows.h>

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

		virtual void OnCreate() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDestroy();
	protected:
		HWND m_Hwnd;
		bool m_IsRun;
	};

}