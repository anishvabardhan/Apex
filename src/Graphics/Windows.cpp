#include "Windows.h"

namespace Apex {

	bool Window::m_Keys[MAX_KEYS];
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	Window::Window(std::string title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		Init();

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}
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
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, key_callback);

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

	void Window::SetClose() const
	{
		glfwSetWindowShouldClose(m_Window, true);
	}

	void Window::Update() const
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	bool Window::IsKeyPressed(unsigned int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

}