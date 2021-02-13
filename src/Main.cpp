#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Graphics/Window.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBufferLayout.h"

using namespace Apex;

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main()
{
	// Creating A Window
	Window* window;
	window = new Window("Apex", 640, 480);
	{
		float vertices[] = {
		   -0.5f,-0.5f,
			0.5f,-0.5f,
			0.5f, 0.5f,
		   -0.5f, 0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Creating VertexArray
		VertexArray va;

		// Creating VertexBuffer
		VertexBuffer vb(vertices, 4 * 2 * sizeof(float));

		// Creating Buffer Layout
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		// Creating IndexBuffer
		IndexBuffer ib(indices, 6);

		ShaderProgramSource source = ParseShader("res/Shaders/Basic.shader");
		unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		glUseProgram(shader);

		int location = glGetUniformLocation(shader, "u_Color");
		glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

		glBindVertexArray(0);
		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// The Core Game Loop
		while (!window->Close())
		{
			// Calling glClear()
			window->Clear();

			glUseProgram(shader);
			va.Bind();
			ib.Bind();

			// Rendering
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			// Updating the Window every loop
			window->Update();
		}

		glDeleteProgram(shader);
	}
	return 0;
}