#include "Window.h"

#include <gl/GL.h>

namespace Apex {

	Window* window = nullptr;

	Window::Window()
		:m_IsRun(false), m_Hwnd(NULL), m_OurWindowHandleToDeviceContext(NULL), m_OurWindowHandleToRenderContext(NULL)
	{
	}

	Window::~Window()
	{
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_CREATE:
		{
			window->OnCreate(hwnd);
			break;
		}

		case WM_DESTROY:
		{
			window->OnDestroy(window->GetRenderContext());
			::PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{
			window->GetKey[wparam] = true;
			break;
		}

		case WM_KEYUP:
		{
			window->GetKey[wparam] = false;
			break;
		}

		case WM_LBUTTONDOWN:
		{
			window->GetMouse[wparam] = true;
			break;
		}

		case WM_LBUTTONUP:
		{
			window->GetMouse[wparam] = false;
			break;
		}

		case WM_RBUTTONDOWN:
		{
			window->GetMouse[wparam] = true;
			break;
		}

		case WM_RBUTTONUP:
		{
			window->GetMouse[wparam] = false;
			break;
		}

		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return NULL;
	}

	bool Window::Init()
	{
		WNDCLASSEX wc;
		wc.cbClsExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = NULL;
		wc.lpszClassName = L"MyWindowClass";
		wc.lpszMenuName = L"";
		wc.style = NULL;
		wc.lpfnWndProc = &WndProc;

		if (!::RegisterClassEx(&wc))
			return false;

		if (!window)
			window = this;

		m_Hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Apex2D", WS_OVERLAPPEDWINDOW, 0, 0, 1024, 768, NULL, NULL, NULL, NULL);

		if (!m_Hwnd)
			return false;

		::ShowWindow(m_Hwnd, SW_SHOW);

		m_IsRun = true;

		return true;
	}

	bool Window::Broadcast()
	{
		MSG msg;

		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		window->OnUpdate();

		Sleep(0);

		return true;
	}

	bool Window::Release()
	{
		if (!::DestroyWindow(m_Hwnd))
			return false;

		return true;
	}

	bool Window::IsRun()
	{
		return m_IsRun;
	}

	void Window::SwappingBuffers()
	{
		SwapBuffers(GetInstance()->GetDeviceContext());
	}

	BOOL Window::MakeContextCurrent(HDC hdc, HGLRC hglrc)
	{
		return wglMakeCurrent(hdc, hglrc);
	}
	
	HGLRC Window::CreateOldRenderContext(HDC hdc)
	{
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 32;
		pfd.cStencilBits = 0;
		pfd.iLayerType = PFD_MAIN_PLANE;
	
		int pixel_format = ::ChoosePixelFormat(hdc, &pfd);
		if (pixel_format == NULL)
			return NULL;
	
		if (!::SetPixelFormat(hdc, pixel_format, &pfd))
			return NULL;
	
		HGLRC context = wglCreateContext(hdc);
		if (context == NULL)
			return NULL;
	
		return context;
	}


	void Window::OnCreate(HWND hwnd)
	{
		m_OurWindowHandleToDeviceContext = GetDC(hwnd);
		
		m_OurWindowHandleToRenderContext = CreateOldRenderContext(m_OurWindowHandleToDeviceContext);
		
		MakeContextCurrent(m_OurWindowHandleToDeviceContext, m_OurWindowHandleToRenderContext);

		glLineWidth(1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::OnUpdate()
	{
		::UpdateWindow(m_Hwnd);
	}

	void Window::OnDestroy(HGLRC rendercontext)
	{
		m_IsRun = false;
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_OurWindowHandleToRenderContext);
		if (!ReleaseDC(m_Hwnd, m_OurWindowHandleToDeviceContext))
			MessageBox(m_Hwnd, L"Cannot Release !!", L"ERROR!!", MB_OK);
	}

	Window* Window::GetInstance()
	{
		return window;
	}

}