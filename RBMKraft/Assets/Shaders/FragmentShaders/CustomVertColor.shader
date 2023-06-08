#version 330 core

in vec3 oColor;
in vec2 oTexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, oTexCoord);
}