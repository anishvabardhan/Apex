#include "Window.h"

namespace Apex {

	Window* window = nullptr;

	Window::Window()
		:m_IsRun(false), m_Hwnd(NULL)
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
			window->OnCreate();
			break;
		}

		case WM_DESTROY:
		{
			window->OnDestroy();
			::PostQuitMessage(0);
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

		m_Hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"Apex2D", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);

		if (!m_Hwnd)
			return false;

		::ShowWindow(m_Hwnd, SW_SHOW);
		::UpdateWindow(m_Hwnd);

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

	void Window::OnCreate()
	{
	}

	void Window::OnUpdate()
	{
	}

	void Window::OnDestroy()
	{
		m_IsRun = false;
	}

}