#version 330 core

in vec2 oTexCoord;

out vec4 FragColor;

uniform sampler2D oTexture;

void main()
{
	FragColor = texture(oTexture, oTexCoord);
}