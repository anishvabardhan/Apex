#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace Apex;

int main()
{
	// Creating A Window
	Window* window;
	window = new Window("Apex", 640, 480);
	{
		// Creating Shader
		Shader shader("res/Shaders/Basic.shader");
		shader.Bind();

		// Renderables
		Renderable2D sprite(glm::vec3(0, 0, 0), glm::vec2(620, 460), shader);

		// Creating an orthographic camera
		glm::mat4 proj = glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), -1.0f, 1.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), sprite.GetPosition());
		glm::mat4 mvp = proj * model;

		// Setting Uniforms
		shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		sprite.GetVAO()->UnBind();
		sprite.GetIBO()->UnBind();
		sprite.GetVBO()->UnBind();
		shader.UnBind();

		// Creating the Renderer
		Renderer renderer;

		// The Core Game Loop
		while (!window->Close())
		{
			// Calling glClear()
			window->Clear();

			// Rendering
			renderer.Draw(sprite);

			// Updating the Window every loop
			window->Update();
		}
	}
	return 0;
}