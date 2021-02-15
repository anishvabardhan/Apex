#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"

#include "Physics/2D/Collision2D.h"

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
		Renderable2D sprite(glm::vec3(370, 220, 0), glm::vec2(20, 20), shader);
		Renderable2D sprite2(glm::vec3(270, 220, 0), glm::vec2(20, 20), shader);

		// Creating an orthographic camera
		glm::mat4 proj = glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), -1.0f, 1.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), sprite.GetPosition());
		glm::mat4 mvp = proj * model;

		// Setting Uniforms
		shader.SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		sprite.GetVAO()->UnBind();
		sprite.GetIBO()->UnBind();
		sprite.GetVBO()->UnBind();
		shader.UnBind();

		// Creating collision objects
		Collision2D collisionA, collisionB, collisionC;

		// Creating the Renderer
		Renderer renderer;

		// The Core Game Loop
		while (!window->Close())
		{
			// Calling glClear()
			window->Clear();

			// Updating the position of the sprite
			sprite.SetPosition(glm::vec3(sprite.GetPosition().x - collisionA.GetX() - collisionC.GetX(), sprite.GetPosition().y, 0));
			//sprite2.SetPosition(glm::vec3(sprite2.GetPosition().x + collisionB.GetX(), sprite2.GetPosition().y, 0));

			// Checking Collision Detection
			collisionA.CollisionWorld(sprite, *window);
			collisionB.CollisionWorld(sprite2, *window);
			collisionC.CollisionObjects(sprite, sprite2);


			// Rendering
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), sprite.GetPosition());
				glm::mat4 mvp = proj * model;
				shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(sprite);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), sprite2.GetPosition());
				glm::mat4 mvp = proj * model;
				shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(sprite2);
			}
			// Updating the Window every loop
			window->Update();
		}
	}
	return 0;
}