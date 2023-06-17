#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 proj;
uniform mat4 objPos;

out vec2 oTexCoord;

void main()
{
	oTexCoord = aTexCoord;
	gl_Position = proj * objPos * vec4(aPos, 1.0f);
}