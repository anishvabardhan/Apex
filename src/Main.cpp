#include "Graphics/Window.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/Renderer.h"

using namespace Apex;

int main()
{
	// Creating A Window
	Window* window;
	window = new Window("Apex", 640, 480);
	{
		float vertices[] = {
		   -0.5f,-0.5f,
			0.5f,-0.5f,
			0.5f, 0.5f,
		   -0.5f, 0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Creating VertexArray
		VertexArray va;

		// Creating VertexBuffer
		VertexBuffer vb(vertices, 4 * 2 * sizeof(float));

		// Creating Buffer Layout
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		// Creating IndexBuffer
		IndexBuffer ib(indices, 6);

		// Creating Shader
		Shader shader("res/Shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		va.UnBind();
		vb.UnBind();
		ib.UnBind();
		shader.UnBind();

		// Creating the Renderer
		Renderer renderer;

		// The Core Game Loop
		while (!window->Close())
		{
			// Calling glClear()
			window->Clear();

			// Rendering
			renderer.Draw(va, ib, shader);

			// Updating the Window every loop
			window->Update();
		}
	}
	return 0;
}