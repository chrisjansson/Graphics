#include "TerrainRenderer.h"
#include "../../NoiseTerrain.h"
#include "../../VerticesFromDataGenerator.h"
#include <cmath>
#include "../../VertexAttribute.h"

TerrainRenderer::TerrainRenderer(ProjectionSettings projectionSettings) : BaseRenderer(projectionSettings)
{
}

void TerrainRenderer::ProjectionMatrixChanged() 
{
	resources.Program.Use();

	resources.Uniforms.CameraToClipMatrixUniform.Upload(_projectionMatrix);

	glUseProgram(0);
}

void TerrainRenderer::Render(float elapsedTime) 
{
	glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	glm::mat4 modelViewMatrix = glm::lookAt(glm::vec3(0.f, -100.f, 100.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 rotationMatrix = glm::rotate(modelViewMatrix, 0.f, glm::vec3(0.f, 0.f, 1.f));

	float x = 32 * cos(elapsedTime / 10);
	float y = 32 * sin(elapsedTime / 10);
	glm::vec4 lightPosition = glm::vec4(x, y, 20, 1.f);

	resources.Program.Use();

	resources.Uniforms.ModelToCameraMatrixUniform.Upload(rotationMatrix);

	glm::vec4 lightPositionCameraSpace = rotationMatrix * lightPosition;
	resources.Uniforms.DirToLightUniform.Upload(lightPositionCameraSpace);

	glm::mat3 normMatrix(rotationMatrix);
	resources.Uniforms.NormalModelToCameraMatrixUniform.Upload(normMatrix);

	resources.Uniforms.LightIntensityUniform.Upload(glm::vec4(0.8f, 0.8f, 0.8f, 0.8f));

	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, ((terrainWidth-1)*(terrainHeight-1)*6), GL_UNSIGNED_INT, resources.indices);
	glBindVertexArray(0);

    glUseProgram(0);
}

void TerrainRenderer::Initialize()
{
	// Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	terrainWidth = 128;
	terrainHeight = 128;

	g_lightDirection = glm::vec4(100.f, 0.f, 100.0f, 0.0f);

	Shader vs(GL_VERTEX_SHADER);
	vs.Load("data/PerFragmentLighting.vert");
	vs.Compile();

	Shader fs(GL_FRAGMENT_SHADER);
	fs.Load("data/PerFragmentLighting.frag");
	fs.Compile();

	resources.Program.AttachShader(vs);
	resources.Program.AttachShader(fs);

	resources.Program.Link();

	LoadUniforms();

	InitializeVertexBuffer();
}

void TerrainRenderer::InitializeVertexBuffer()
{
	NoiseTerrain2D terrain(terrainWidth, terrainHeight, 10, 6.f, 10.f, 4711);
	terrain.GenerateData();

	VertexPositionNormal* vertices;
	VerticesAndIndicesFromData(terrain.GetData(), terrainWidth, terrainHeight, &vertices, &resources.indices);

	CreateVertexArrayObject(vertices, &vertexArrayObject, &resources.vertexBuffer, terrainWidth*terrainHeight);

	delete[] vertices;
}

void TerrainRenderer::LoadUniforms()
{
	resources.Uniforms.ModelToCameraMatrixUniform = Uniform<glm::mat4>(LoadUniform("modelToCameraMatrix"));
	resources.Uniforms.DirToLightUniform = Uniform<glm::vec4>(LoadUniform("lightPosition"));
	resources.Uniforms.NormalModelToCameraMatrixUniform = Uniform<glm::mat3>(LoadUniform("normalModelToCameraMatrix"));
	resources.Uniforms.LightIntensityUniform = Uniform<glm::vec4>(LoadUniform("lightIntensity"));
	resources.Uniforms.CameraToClipMatrixUniform = Uniform<glm::mat4>(LoadUniform("cameraToClipMatrix"));
}

void TerrainRenderer::Finalize() 
{
	resources.Program.Delete();
	resources.FragmentShader.Delete();
	resources.VertexShader.Delete();

	glDeleteBuffers(1, &resources.vertexBuffer);

	delete[] resources.indices;
}

GLint TerrainRenderer::LoadUniform(char const *uniformName)
{
	return glGetUniformLocation(resources.Program.GetProgram(), uniformName);
}