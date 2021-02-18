#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderer.h"

#include "Physics/2D/Collision2D.h"

#include "Maths/Mat4.h"

using namespace Apex;

int main()
{
// Creating A Window--------------------------------------------------------------------------------------------
	
	Window* window;
	window = new Window("Apex", 640, 480);
	{
// Creating Shader------------------------------------------------------------------------------------------
		
		Shader shader("res/Shaders/Basic.shader");
		shader.Bind();

// Renderables
		
		Renderable2D sprite(Vec3(300, 200, 0), Vec2(20, 20), shader);
		Renderable2D food(Vec3(500, 300, 0), Vec2(20, 20), shader);
		Renderable2D WallBottom(Vec3(0, 0, 0), Vec2(640, 20), shader);
		Renderable2D WallTop(Vec3(0, 460, 0), Vec2(640, 20), shader);
		Renderable2D WallLeft(Vec3(0, 20, 0), Vec2(20, 480), shader);
		Renderable2D WallRight(Vec3(620, 20, 0), Vec2(20, 440), shader);

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
		
		Collision2D collision;

// Creating the Renderer------------------------------------------------------------------------------------
		
		Renderer renderer;

		float a = 2.0f, b = 0.0f, c = 100.0f, d = 50.0f;

// The Core Game Loop---------------------------------------------------------------------------------------
		
		while (!window->Close())
		{
// Calling glClear()----------------------------------------------------------------------------------------
			
			window->Clear();

// Updating the sprite position through input---------------------------------------------------------------
			
			sprite.SetPosition(Vec3(sprite.GetPosition().m_X + a, sprite.GetPosition().m_Y + b, 0.0f));
			
			model = Mat4::translation(sprite.GetPosition());

			if (window->IsKeyPressed(GLFW_KEY_W))
			{
				b = 2.0f;
				a = 0.0f;
			}

			if (window->IsKeyPressed(GLFW_KEY_S))
			{
				b = -2.0f;
				a = 0.0f;
			}

			if (window->IsKeyPressed(GLFW_KEY_A))
			{
				a = -2.0f;
				b = 0.0f;
			}

			if (window->IsKeyPressed(GLFW_KEY_D))
			{
				a = 2.0f;
				b = 0.0f;
			}

// Checking for collisions----------------------------------------------------------------------------------
			
			if (collision.CollisionObjects(sprite, WallTop))
			{
				window->SetClose();
			}

			if (collision.CollisionObjects(sprite, WallBottom))
			{
				window->SetClose();
			}

			if (collision.CollisionObjects(sprite, WallLeft))
			{
				window->SetClose();
			}

			if (collision.CollisionObjects(sprite, WallRight))
			{
				window->SetClose();
			}

			//if (collision.CollisionObjects(sprite, food))
			//{
			//	food.SetPosition(Vec3(food.GetPosition().m_X - (c * collision.GetX()), food.GetPosition().m_Y - (d * collision.GetY()), 0));
			//}

// Rendering------------------------------------------------------------------------------------------------
			
			// Rendering the body---------------------------------------------------------------------------
			
			{
				shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
				model = Mat4::translation(sprite.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(sprite);
			}

			// Rendering the food---------------------------------------------------------------------------

			{
				shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
				model = Mat4::translation(food.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(food);
			}

			// Rendering the bottom wall--------------------------------------------------------------------
			
			{
				shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
				model = Mat4::translation(WallBottom.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(WallBottom);
			}

			// Rendering the top wall-----------------------------------------------------------------------
			
			{
				shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
				model = Mat4::translation(WallTop.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(WallTop);
			}

			// Rendering the left wall----------------------------------------------------------------------
			
			{
				shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
				model = Mat4::translation(WallLeft.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(WallLeft);
			}

			// Rendering the right wall---------------------------------------------------------------------
			
			{
				shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
				model = Mat4::translation(WallRight.GetPosition());
				shader.SetUniformMat4f("model", model);

				renderer.Draw(WallRight);
			}

// Updating the Window every loop---------------------------------------------------------------------------
			
			window->Update();
		}
	}
	return 0;
}