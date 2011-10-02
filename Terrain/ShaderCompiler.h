#include <GL\glew.h>
#include <fstream>
#include <sstream>
#include <vector>

std::string LoadShaderStringFromFile(const std::string &shaderFileName);

void printShaderInfoLog(GLuint shader);

GLuint CreateShader(GLenum shaderType, const char* cStrShaderFile);

void printProgramInfoLog(GLuint program);

GLuint CreateProgram(const std::vector<GLuint>& shaders);

void DeleteShaderProgram(GLuint program, const std::vector<GLuint>& shaders);