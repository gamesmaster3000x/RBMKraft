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
	ID = glCreateProgram();
	for (unsigned short i = 0; i < 6; i++)
	{
		if (shaders[i])
		{
			glAttachShader(ID, shaders[i]);
		}
	}
}

ShaderProgram::ShaderProgram()
{
	ID = 0;
}

bool ShaderProgram::LinkProgram()
{
	fprintf(stdout, "Linking shader program...\n");

	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
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
	glUseProgram(ID);
}

void ShaderProgram::SetMat4(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, glm::value_ptr(value));
}
