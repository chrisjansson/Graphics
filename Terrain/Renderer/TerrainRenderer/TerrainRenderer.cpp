#include "TerrainRenderer.h"

void GetUniform(GLuint program, GLchar const* uniformName) 
{
	glGetUniformLocation(program, uniformName);
}

void TerrainRenderer::ProjectionMatrixChanged() 
{
	//Upload to shader
}

void TerrainRenderer::Render() 
{
	//Render this scene
}

void TerrainRenderer::Initialize()
{
	//Set up for rendering, allocate shaders and data
}

void TerrainRenderer::Finalize() 
{
	//Clean up after rendering, release resources
}
