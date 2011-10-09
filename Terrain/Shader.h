#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
public:
	Shader(GLenum shaderType);
	void Load(std::string const &fileName);
	void Compile();
	void Delete();
	GLuint GetShaderObject() const { return _shader; }
private:
	GLenum _shaderType;
	GLuint _shader;

	GLuint CreateShader(GLenum shaderType, const char* cStrShaderFile);
	void PrintShaderInfoLog(GLuint shader);
};


#endif