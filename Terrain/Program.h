#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL\glew.h>
#include <iostream>
#include <vector>

#include "Shader.h"

class Program
{
public:
	Program();
	void AttachShader(Shader const &shader);
	//void DetachShader(Shader const &shader);
	void Delete();
	void Link();
	void Use();
	GLuint GetProgram() { return _program; }
private:
	GLuint _program;
	std::vector<Shader> _shaders;
	void PrintProgramInfoLog(GLuint program);
};

#endif