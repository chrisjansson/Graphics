#include "Shader.h"

std::string const * LoadFile(std::string const &fileName)
{
	std::ifstream shaderFile(fileName, std::ifstream::in);

	if(!shaderFile.is_open()) 
	{
		return nullptr;
	}

	std::stringstream shaderData;
	shaderData << shaderFile.rdbuf();
	shaderFile.close();

	std::string *strShaderFile = new std::string(shaderData.str());
		
	return strShaderFile;
}

Shader::Shader() { }

Shader::Shader(GLenum shaderType) 
{
	this->_shaderType = shaderType;
}

void Shader::Load(std::string const &fileName) 
{
	std::string const * shaderString = LoadFile(fileName);

	this->_shader = CreateShader(this->_shaderType, shaderString->c_str());
	
	delete shaderString;
}

void Shader::Compile() 
{
	glCompileShader(_shader);

	GLint shaderStatus;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &shaderStatus);
	if(shaderStatus == GL_FALSE)
	{
		PrintShaderInfoLog(_shader);
	}
}

void Shader::Delete() 
{
	glDeleteShader(this->_shader);
	this->_shader = 0;
}

GLuint Shader::CreateShader(GLenum shaderType, char const * cStrShaderFile) 
{
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &cStrShaderFile, NULL);

	return shader;
}

void Shader::PrintShaderInfoLog(GLuint shader) 
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
