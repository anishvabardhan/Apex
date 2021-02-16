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

// Creating an orthographic camera--------------------------------------------------------------------------

		Mat4 proj = Mat4::orthographic(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), -1.0f, 1.0f);
		Mat4 model = Mat4::translation(sprite.GetPosition());

// Setting Uniforms-----------------------------------------------------------------------------------------
		
		shader.SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
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

// The Core Game Loop---------------------------------------------------------------------------------------
		
		while (!window->Close())
		{
// Calling glClear()----------------------------------------------------------------------------------------
			
			window->Clear();

// Updating the sprite position-----------------------------------------------------------------------------
			
			sprite.SetPosition(Vec3(sprite.GetPosition().m_X + collisionA.GetX(), sprite.GetPosition().m_Y + collisionA.GetY(), 0.0f));
			model = Mat4::translation(sprite.GetPosition());

// Checking for collisions----------------------------------------------------------------------------------
			
			collisionA.CollisionWorld(sprite, *window);

// Rendering------------------------------------------------------------------------------------------------

			shader.SetUniformMat4f("model", model);
			
			renderer.Draw(sprite);

// Updating the Window every loop---------------------------------------------------------------------------
			
			window->Update();
		}
	}
	return 0;
}