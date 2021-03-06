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

	CreateShader("res/Shaders/Basic.shader");

// Creating Quads---------------------------------------------------------------------------------------------------------------------------------

	Apex::Renderable2D quad(Apex::Vec3(170, 90, 0), Apex::Vec2(100, 100), g_Shader);

// Creating a Camera------------------------------------------------------------------------------------------------------------------------------

	Apex::OrthoGraphic Camera(0.0f, (float)g_Window->GetWidth(), 0.0f, (float)g_Window->GetHeight());

//Setting Uniforms--------------------------------------------------------------------------------------------------------------------------------

	g_Shader.SetUniformMat4f("u_ViewProj", Camera.GetViewProjMatrix());

// Creating a Collision object--------------------------------------------------------------------------------------------------------------------

	Apex::Collision2D collision;

// Creating a Renderer----------------------------------------------------------------------------------------------------------------------------

	Apex::Renderer renderer;

// Instantiating the Game Loop-------------------------------------------------------------------------------------------------------------------

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

		g_Shader.SetUniformMat4f("u_Model", quad.GetModelPosition());

		renderer.Draw(quad);
		
		// Updating the Window every loop---------------------------------------------------------------------------------------------------------

		g_Window->Update();
	}

// Unbinding the members of Renderables-----------------------------------------------------------------------------------------------------------

	quad.UnBind();
}

// Defining a Function to Create a shader---------------------------------------------------------------------------------------------------------

Apex::Shader& BreakOut::CreateShader(const std::string& filepath)
{
	Apex::Shader shader(filepath);
	g_Shader = shader;
	g_Shader.Bind();

	return g_Shader;
}
