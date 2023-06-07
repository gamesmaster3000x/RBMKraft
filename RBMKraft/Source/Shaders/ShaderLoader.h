#ifndef GAMESHADER
#define GAMESHADER
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum Shaders { Vertex = 1, Fragment = 2 };

static class ShaderLoader 
{
public:
	static unsigned int LoadShader(const unsigned int type, const char* name);
};

class ShaderProgram
{
public:
	unsigned int ID;

	ShaderProgram(const unsigned int shaders[6]);

	bool LinkProgram();

	void Use();
};

#endif // !GAMESHADERLOADER

