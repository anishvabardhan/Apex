#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"

#include "Physics/2D/Collision2D.h"

#include "Maths/Mat4.h"

using namespace Apex;

int main()
{
// Creating A Window----------------------------------------------------------------------------------------
	
	Window* window;
	window = new Window("Apex", 640, 480);
	{
// Creating Shader------------------------------------------------------------------------------------------
		
		Shader shader("res/Shaders/Basic.shader");
		shader.Bind();

// Renderables----------------------------------------------------------------------------------------------
		
		Renderable2D sprite(Vec3(300, 200, 0), Vec2(20, 20), shader);
		Renderable2D Block(Vec3(280, 25, 0), Vec2(80, 20), shader);


// Creating an orthographic camera--------------------------------------------------------------------------

		Mat4 proj = Mat4::orthographic(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), -1.0f, 1.0f);
		Mat4 model = Mat4::translation(sprite.GetPosition());

// Setting Uniforms-----------------------------------------------------------------------------------------
		
		shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
		shader.SetUniformMat4f("proj", proj);
		shader.SetUniformMat4f("model", model);

		sprite.GetVAO()->UnBind();
		sprite.GetIBO()->UnBind();
		sprite.GetVBO()->UnBind();
		shader.UnBind();

// Creating collision objects-------------------------------------------------------------------------------
		
		Collision2D collisionA;

// Creating the Renderer------------------------------------------------------------------------------------
		
		Renderer renderer;

		float a = 2.0f;

// The Core Game Loop---------------------------------------------------------------------------------------
		
		while (!window->Close())
		{
// Calling glClear()----------------------------------------------------------------------------------------
			
			window->Clear();

// Updating the sprite position through input---------------------------------------------------------------
			
			sprite.SetPosition(Vec3(sprite.GetPosition().m_X + collisionA.GetX(), sprite.GetPosition().m_Y + collisionA.GetY(), 0.0f));

			model = Mat4::translation(sprite.GetPosition());

			if (window->IsKeyPressed(GLFW_KEY_A) && Block.GetPosition().m_X >= 10)
			{
				Block.SetPosition(Vec3(Block.GetPosition().m_X - a, Block.GetPosition().m_Y, 0.0f));
			}

			if (window->IsKeyPressed(GLFW_KEY_D) && Block.GetPosition().m_X < 550)
			{
				Block.SetPosition(Vec3(Block.GetPosition().m_X + a, Block.GetPosition().m_Y, 0.0f));
			}

// Checking for collisions----------------------------------------------------------------------------------
			
			collisionA.CollisionWorld(sprite, *window);

			if (collisionA.CollisionObjects(sprite, Block))
			{
				collisionA.SetY(-collisionA.GetY());
			}

// Rendering------------------------------------------------------------------------------------------------
			
			// Rendering the body---------------------------------------------------------------------------
			
			{
				shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
				model = Mat4::translation(sprite.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(sprite);
			}

			// Rendering the Block--------------------------------------------------------------------------

			{
				shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
				model = Mat4::translation(Block.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(Block);
			}

// Updating the Window every loop---------------------------------------------------------------------------
			
			window->Update();
		}
	}
	return 0;
}