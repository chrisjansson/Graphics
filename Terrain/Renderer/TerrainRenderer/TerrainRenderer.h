#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "../BaseRenderer.h"
#include "../../Program.h"
#include "../../Shader.h"
#include "../../Uniform.h"

struct TerrainRendererResources 
{
	TerrainRendererResources() {}

	Program Program;
	Shader VertexShader;
	Shader FragmentShader;

	struct 
	{
		/* UniformLocations goes here */
		Uniform<glm::mat4> ModelToCameraMatrixUniform;
		Uniform<glm::vec4> DirToLightUniform;
		Uniform<glm::vec4> LightIntensityUniform;
		Uniform<glm::mat3> NormalModelToCameraMatrixUniform;
		Uniform<glm::mat4> CameraToClipMatrixUniform;
	} Uniforms;

	GLuint vertexBuffer;
	GLuint *indices;
};

class TerrainRenderer : public BaseRenderer
{
public:
	TerrainRenderer(ProjectionSettings projectionSettings);
	void Render(float elapsedTime);
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