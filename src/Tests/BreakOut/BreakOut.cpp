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

// Creating a Camera------------------------------------------------------------------------------------------------------------------------------

	Apex::OrthoGraphic Camera(0.0f, (float)g_Window->GetWidth(), 0.0f, (float)g_Window->GetHeight());

//Setting Uniforms--------------------------------------------------------------------------------------------------------------------------------

	shader.SetUniformMat4f("proj", Camera.GetProjMatrix());

// Creating a Collision object--------------------------------------------------------------------------------------------------------------------

	Apex::Collision2D collision;

// Creating a Renderer----------------------------------------------------------------------------------------------------------------------------

	Apex::Renderer renderer;

	float a = 2.0f;

	while (!g_Window->Close())
	{
		// Calling glClear()----------------------------------------------------------------------------------------------------------------------

		g_Window->Clear();

		// Updating the quad position through input-----------------------------------------------------------------------------------------------

		quad.SetPosition(Apex::Vec3(quad.GetPosition().m_X + collision.GetX(), quad.GetPosition().m_Y + collision.GetY(), 0.0f));

		// Checking for collisions----------------------------------------------------------------------------------------------------------------

		collision.CollisionWorld(quad, *g_Window);

	// Rendering----------------------------------------------------------------------------------------------------------------------------------

		// Rendering the quad---------------------------------------------------------------------------------------------------------------------

		{
			shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);			
			shader.SetUniformMat4f("model", quad.GetModel());

			renderer.Draw(quad);
		}

		// Updating the Window every loop---------------------------------------------------------------------------------------------------------

		g_Window->Update();
	}

// Unbinding the members of Renderables-----------------------------------------------------------------------------------------------------------

	quad.UnBind();

}
