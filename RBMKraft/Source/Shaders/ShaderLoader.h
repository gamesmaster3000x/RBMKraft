#ifndef GAMESHADER
#define GAMESHADER
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

enum Shaders { Vertex = 1, Fragment = 2 };

class ShaderLoader 
{
public:
	static unsigned int LoadShader(const unsigned int type, const char* name);
};

class ShaderProgram
{
public:
	unsigned int ID;

	ShaderProgram();

	ShaderProgram(const unsigned int shaders[6]);

	bool LinkProgram();

	void Use();

	void SetMat4(const char* name, glm::mat4 value);
};

#endif // !GAMESHADERLOADER
