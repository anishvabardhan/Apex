#include "Snake.h"

//Snake::Snake()
//{
//	CreateWindow();
//
//	CreateHead();
//	CreateWorld();
//}
//
//Snake::~Snake()
//{
//}

void Snake::CreateHead()
{
	Apex::Shader shader("res/Shaders/Basic.shader");
	shader.Bind();

	a_Head = new Apex::Renderable2D(Apex::Vec3(0, 0, 0), Apex::Vec2(0, 0), shader);

}

void Snake::CreateWorld()
{
}

void Snake::CreateWindow()
{
	a_Window = new Apex::Window("SnakeGame", 640, 480);
}
