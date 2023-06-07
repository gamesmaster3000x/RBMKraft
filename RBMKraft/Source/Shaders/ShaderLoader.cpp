#include "ShaderLoader.h"

unsigned int ShaderLoader::LoadShader(const unsigned int type, const char* name)
{
	fprintf(stdout, "Loading shader...\n");

	unsigned int id = 0;

	std::string codeTmp;
	std::ifstream file;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		file.open(name);

		std::stringstream stream;

		stream << file.rdbuf();

		file.close();

		codeTmp = stream.str();
	}
	catch(std::ifstream::failure e)
	{
		fprintf(stderr, "Failed to open shader file.");
	}

	const char* code = codeTmp.c_str();
	
	id = glCreateShader(type);
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		fprintf(stderr, infoLog);
		fprintf(stderr, "\n");
	}
	else
	{
		fprintf(stdout, "Sucessfully compiled shader.\n");
	}

	return id;
}

ShaderProgram::ShaderProgram(const unsigned int shaders[6])
{
	this->ID = glCreateProgram();
	for (unsigned short i = 0; i < 6; i++)
	{
		if (shaders[i])
		{
			glAttachShader(this->ID, shaders[i]);
		}
	}
}

bool ShaderProgram::LinkProgram()
{
	fprintf(stdout, "Linking shader program...\n");

	glLinkProgram(this->ID);

	int success;
	char infoLog[512];

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(this->ID, 512, NULL, infoLog);
		fprintf(stderr, infoLog);
		fprintf(stderr, "\n");
	}
	else
	{
		fprintf(stdout, "Sucessfully linked shader program.\n");
	}

	return success;
}

void ShaderProgram::Use()
{
	glUseProgram(this->ID);
}