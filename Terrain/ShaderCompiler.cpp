#include "ShaderCompiler.h"

std::string LoadShaderStringFromFile(const std::string &shaderFileName)
{
	std::ifstream shaderFile(shaderFileName, std::ifstream::in);

	if(!shaderFile.is_open()) 
	{
		fprintf(stderr, "Cannot load shader file %s\n", shaderFileName.c_str());
		return NULL;
	}

	std::stringstream shaderData;
	shaderData << shaderFile.rdbuf();
	shaderFile.close();

	std::string strShaderFile =	shaderData.str();
	return strShaderFile;
	//const char* cStrShaderFile = strShaderFile.c_str();

	//return cStrShaderFile;
}

void printShaderInfoLog(GLuint shader) 
{
	GLint infoLogLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if(infoLogLength > 0) 
	{
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
		fprintf(stderr, "%s\n", infoLog);
		delete[] infoLog;
	}	
}

GLuint CreateShader(GLenum shaderType, const char* cStrShaderFile) 
{
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &cStrShaderFile, NULL);

	glCompileShader(shader);

	GLint shaderStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderStatus);
	if(shaderStatus == GL_FALSE)
	{
		printShaderInfoLog(shader);
	}

	return shader;
}

void printProgramInfoLog(GLuint program) 
{
	GLint infoLogLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

	if(infoLogLength > 0)
	{
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
		fprintf(stderr, "%s\n", infoLog);
		delete[] infoLog;
	}
}

GLuint CreateProgram(const std::vector<GLuint>& shaders)
{
	GLuint program = glCreateProgram();

	for(int i=0; i < shaders.size(); i++) 
	{
		glAttachShader(program, shaders[i]);
	}

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		printProgramInfoLog(program);
	}

	return program;
}

void DeleteShaderProgram(GLuint program, const std::vector<GLuint>& shaders) 
{
	for(int i=0; i < shaders.size(); i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
		
	glDeleteProgram(program);
}