#include "BreakOut.h"

// Defining the Constructor-----------------------------------------------------------------------------------------------------------------------

BreakOut::BreakOut(int width, int height, std::string title)
	: g_Width(width), g_Height(height), g_Title(title)
{
	Init();
}

// Defining the Destructor------------------------------------------------------------------------------------------------------------------------

BreakOut::~BreakOut()
{

}

void BreakOut::Init()
{
// Creating a Window------------------------------------------------------------------------------------------------------------------------------

	g_Window = new Apex::Window(g_Title, g_Width, g_Height);

// Creating a Shader------------------------------------------------------------------------------------------------------------------------------

	Apex::Shader shader("res/Shaders/Basic.shader");
	shader.Bind();

// Creating Quads---------------------------------------------------------------------------------------------------------------------------------

	Apex::Renderable2D quad(Apex::Vec3(300, 200, 0), Apex::Vec2(20, 20), shader);
	Apex::Renderable2D Block(Apex::Vec3(280, 25, 0), Apex::Vec2(80, 20), shader);

// Creating a Camera------------------------------------------------------------------------------------------------------------------------------

	Apex::OrthoGraphic Camera(0.0f, (float)g_Window->GetWidth(), 0.0f, (float)g_Window->GetHeight());

// Creating a Model of Quad-----------------------------------------------------------------------------------------------------------------------

	Apex::Mat4 model = Apex::Mat4::translation(quad.GetPosition());

//Setting Uniforms--------------------------------------------------------------------------------------------------------------------------------

	shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.SetUniformMat4f("proj", Camera.GetProjMatrix());
	shader.SetUniformMat4f("model", model);

	quad.GetVAO()->UnBind();
	quad.GetIBO()->UnBind();
	quad.GetVBO()->UnBind();
	shader.UnBind();

// Creating a Collision object--------------------------------------------------------------------------------------------------------------------

	Apex::Collision2D collisionA;

// Creating a Renderer----------------------------------------------------------------------------------------------------------------------------

	Apex::Renderer renderer;

	float a = 2.0f;

	while (!g_Window->Close())
	{
		// Calling glClear()----------------------------------------------------------------------------------------------------------------------

		g_Window->Clear();

		// Updating the quad position through input-----------------------------------------------------------------------------------------------

		quad.SetPosition(Apex::Vec3(quad.GetPosition().m_X + collisionA.GetX(), quad.GetPosition().m_Y + collisionA.GetY(), 0.0f));

		model = Apex::Mat4::translation(quad.GetPosition());

		if (g_Window->IsKeyPressed(GLFW_KEY_A) && Block.GetPosition().m_X >= 10)
		{
			Block.SetPosition(Apex::Vec3(Block.GetPosition().m_X - a, Block.GetPosition().m_Y, 0.0f));
		}

		if (g_Window->IsKeyPressed(GLFW_KEY_D) && Block.GetPosition().m_X < 550)
		{
			Block.SetPosition(Apex::Vec3(Block.GetPosition().m_X + a, Block.GetPosition().m_Y, 0.0f));
		}

		// Checking for collisions----------------------------------------------------------------------------------------------------------------

		collisionA.CollisionWorld(quad, *g_Window);

		if (collisionA.CollisionObjects(quad, Block))
		{
			collisionA.SetY(-collisionA.GetY());
		}

	// Rendering----------------------------------------------------------------------------------------------------------------------------------

		// Rendering the body---------------------------------------------------------------------------------------------------------------------

		{
			shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
			model = Apex::Mat4::translation(quad.GetPosition());
			shader.SetUniformMat4f("model", model);

			renderer.Draw(quad);
		}

		// Rendering the Block--------------------------------------------------------------------------------------------------------------------
		{
			shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
			model = Apex::Mat4::translation(Block.GetPosition());
			shader.SetUniformMat4f("model", model);

			renderer.Draw(Block);
		}

		// Updating the Window every loop---------------------------------------------------------------------------------------------------------

		g_Window->Update();
	}
}
