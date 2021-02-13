#include "Window.h"

namespace Apex {

	Window::Window(std::string title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		Init();
	}

	Window::~Window()
	{
	}

	int Window::Init()
	{
		if (!glfwInit())
			return -1;

		if (!glewInit())
			return -1;

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_Window);
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool Window::Close() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Update() const
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

}