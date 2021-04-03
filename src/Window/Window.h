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
		
		BOOL MakeContextCurrent(HDC hdc, HGLRC hglrc);

		HGLRC CreateRenderContext(HDC hdc);

		virtual void OnCreate(HWND hwnd);
		virtual void OnUpdate();
		virtual void OnDestroy(HGLRC rendercontext);

		inline HDC GetDeviceContext() const { return m_OurWindowHandleToDeviceContext; }
		inline HGLRC GetRenderContext() const { return m_OurWindowHandleToRenderContext; }
	protected:
		HWND m_Hwnd;
		bool m_IsRun;
		HDC m_OurWindowHandleToDeviceContext;
		HGLRC m_OurWindowHandleToRenderContext;
	};

}