#include "Program.h"

Program::Program()
{
	this->_program = glCreateProgram();
}

void Program::AttachShader(Shader const &shader) 
{
	_shaders.push_back(shader);

	glAttachShader(this->_program, shader.GetShaderObject());
}

void Program::Delete()
{
	for(GLuint i=0; i < _shaders.size(); i++)
		glDetachShader(_program, _shaders[i].GetShaderObject());

	_shaders.clear();

	glDeleteProgram(this->_program);
	this->_program = 0;
}

void Program::Link() 
{
	glLinkProgram(_program);

	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		PrintProgramInfoLog(_program);
	}
}

void Program::PrintProgramInfoLog(GLuint program) 
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

void Program::Use() 
{
	glUseProgram(_program);
}