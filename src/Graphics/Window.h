#pragma once
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Apex {

	class Window
	{
		std::string m_Title;
		int m_Width;
		int m_Height;
		GLFWwindow* m_Window;
	public:
		Window(std::string title, int width, int height);
		~Window();

		int Init();
		void Clear() const;
		bool Close() const;
		void Update() const;
	};

}