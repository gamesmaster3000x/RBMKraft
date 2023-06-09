#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aBrightness;
layout (location = 2) in vec2 aTexCoord;

out vec2 oTexCoord;
out float oBrightness;

void main()
{
	oTexCoord = aTexCoord;
	oBrightness = aBrightness;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}