#pragma once
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS  1024

namespace Apex {

	class Window
	{
		std::string m_Title;
		int m_Width;
		int m_Height;
		GLFWwindow* m_Window;
	
		static bool m_Keys[MAX_KEYS];
	public:
		explicit Window(std::string title, int width, int height);
		~Window();

		int Init();
		void Clear() const;
		bool Close() const;
		void SetClose() const;
		void Update() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		static bool IsKeyPressed(unsigned int keycode);
	private:
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};

}