#shader vertex
#version 330 core

layout(location = 0) in vec4 vertex;

out vec2 TexCoord;

uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * vec4(vertex.xy, 0.0, 1.0);
	TexCoord = vertex.zw;
};

#shader fragment
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D u_Text;
uniform vec4 u_TextColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Text, TexCoord).r);
	FragColor = u_TextColor * sampled;
};