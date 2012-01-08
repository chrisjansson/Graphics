#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "Renderer/BaseRenderer.h"
#include "Utilities/Program.h"
#include "Utilities/Shader.h"
#include "Utilities/Uniform.h"
#include "MeshContainers/UnitCube.h"

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
	void InitializeVertexBuffer();

	glm::vec4 g_lightDirection;
	int terrainWidth; 
	int terrainHeight;
	GLuint vertexArrayObject;

	UnitCube _unitCube;
};

#endif