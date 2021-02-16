#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
		
uniform mat4 proj;
uniform mat4 model = mat4(1.0f);

void main()
{
    gl_Position = proj * model * position;
};

#shader fragment
#version 330 core
		
layout(location = 0) out vec4 color;
		
uniform vec4 u_Color;

void main()
{
    color = u_Color;
};