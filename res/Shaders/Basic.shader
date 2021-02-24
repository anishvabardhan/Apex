#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
		
//uniform mat4 proj;
uniform mat4 u_ViewProj = mat4(1.0f);
uniform mat4 u_Model = mat4(1.0f);

void main()
{
    gl_Position = u_ViewProj * u_Model * position;
};

#shader fragment
#version 330 core
		
layout(location = 0) out vec4 color;
		
uniform vec4 u_Color;

void main()
{
    color = u_Color;
};