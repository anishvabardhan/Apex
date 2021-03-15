#include "AstroidGameMode.h"

AstroidGameMode::AstroidGameMode(int width, int height, std::string title)
	:g_Width(width), g_Height(height), g_Title(title)
{
	CreateGame();
}

AstroidGameMode::~AstroidGameMode()
{
}

void AstroidGameMode::CreateGame()
{
	g_Window = new Apex::Window(g_Title, g_Width, g_Height);

	CreateShader("res/Shaders/Basic.shader");

	Astroid as1(Apex::Vec3(300, 200, 0), g_Shader);

	Apex::OrthoGraphic Camera(0.0f, (float)g_Window->GetWidth(), 0.0f, (float)g_Window->GetHeight());

	g_Shader.SetUniformMat4f("u_ViewProj", Camera.GetViewProjMatrix());

	Apex::Collision2D c_CollisionA;

	Apex::Renderer r_Renderer;

	while (!g_Window->Close())
	{
		g_Window->Clear();

		as1.SetPosition(Apex::Vec3(as1.GetPosition().m_X + c_CollisionA.GetX(), as1.GetPosition().m_Y + c_CollisionA.GetY(), 0.0f));
		
		c_CollisionA.CollisionWorld(as1, *g_Window);

		{
			g_Shader.SetUniformMat4f("u_Model", as1.GetAstroidPosition());
			r_Renderer.Draw(as1);
		}

		g_Window->Update();
	}

	as1.UnBind();
}

Apex::Shader& AstroidGameMode::CreateShader(const std::string& filepath)
{
	Apex::Shader shader(filepath);
	g_Shader = shader;
	g_Shader.Bind();

	return g_Shader;
}
