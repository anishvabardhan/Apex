#include "Window.h"

namespace Apex {

	Window::Window(std::string title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		Init();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	int Window::Init()
	{
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_Window);

		glfwSwapInterval(1);

		if (!glewInit())
			return -1;
		return 0;
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