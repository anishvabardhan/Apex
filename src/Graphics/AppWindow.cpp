#include "AppWindow.h"

namespace Apex {

	long __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_DESTROY:
			std::cout << "\ndestroying window\n";
			PostQuitMessage(0);
			return 0L;
		case WM_LBUTTONDOWN:
			std::cout << "\nmouse left button down at (" << LOWORD(lp)
				<< ',' << HIWORD(lp) << ")\n";
			// fall thru
		default:
			return DefWindowProc(window, msg, wp, lp);
		}
	}


	AppWindow::AppWindow(int width, int height)
		: m_Width(width), m_Height(height)
	{
		Init();
	}

	AppWindow::~AppWindow()
	{
	}

	int AppWindow::Init()
	{
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		const char* const myclass = "myclass";

		WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
		0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
		LoadCursor(0,IDC_ARROW),  (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0))),
		0, (LPCWSTR)myclass, LoadIcon(0,IDI_APPLICATION) };

		if (RegisterClassEx(&wndclass))
		{
			m_Window = CreateWindowEx(0, (LPCWSTR)myclass, L"Apex2D",
				WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				m_Width, m_Height, NULL, NULL, GetModuleHandle(0), 0);

			if (m_Window)
			{
				ShowWindow(m_Window, SW_SHOWDEFAULT);
				MSG msg;
				while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
			}
		}

		if (!m_Window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent((GLFWwindow*)m_Window);

		glfwSwapInterval(1);

		if (!glewInit())
			return -1;
		return 0;
	}

	void AppWindow::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool AppWindow::Close() const
	{
		return glfwWindowShouldClose((GLFWwindow*)m_Window);
	}

	void AppWindow::SetClose() const
	{
		glfwSetWindowShouldClose((GLFWwindow*)m_Window, true);
	}

	void AppWindow::Update() const
	{
		glfwSwapBuffers((GLFWwindow*)m_Window);
		glfwPollEvents();
	}

}