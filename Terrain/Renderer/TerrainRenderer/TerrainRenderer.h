#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "../BaseRenderer.h"
#include "../../Program.h"
#include "../../Shader.h"

struct TerrainRendererResources 
{
	Program Program;
	Shader VertexShader;
	Shader FragmentShader;

	struct 
	{
		/* UniformLocations goes here */
		GLint ModelToCameraMatrix;
		GLint NormalModelToCameraMatrixUnif;
		GLint DirToLightUnif;
		GLint LightIntensityUnif;
		GLint CameraToClipMatrix;
	} Uniforms;

	GLuint vertexBuffer;
	GLuint *indices;
};

class TerrainRenderer : BaseRenderer
{
public:
	void Render();
	void Initialize();
	void Finalize();
private:
	TerrainRendererResources resources;
	GLint LoadUniform(char const *uniformName);
	void ProjectionMatrixChanged();
	void LoadUniforms();

	glm::vec4 g_lightDirection;
	int terrainWidth; 
	int terrainHeight;
};

#endif