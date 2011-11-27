#include "TerrainRenderer.h"
#include "../../NoiseTerrain.h"
#include "../../VerticesFromDataGenerator.h"

void TerrainRenderer::ProjectionMatrixChanged() 
{
	resources.Program.Use();

	glUniformMatrix4fv(resources.Uniforms.CameraToClipMatrix, 1, GL_FALSE, glm::value_ptr(this->_projectionMatrix));

	glUseProgram(0);
}

void TerrainRenderer::Render() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 modelViewMatrix = glm::lookAt(glm::vec3(0.f, 100.f, 50.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 rotationMatrix = glm::rotate(modelViewMatrix, 0.f, glm::vec3(0.f, 0.f, 1.f));

	glm::vec4 lightDirCameraSpace = glm::normalize(modelViewMatrix * g_lightDirection);
    
	resources.Program.Use();

	glUniform3fv(resources.Uniforms.DirToLightUnif, 1, glm::value_ptr(lightDirCameraSpace));
	glUniformMatrix4fv(resources.Uniforms.ModelToCameraMatrix, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glm::mat3 normMatrix(rotationMatrix);
	glUniformMatrix3fv(resources.Uniforms.NormalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
	glUniform4f(resources.Uniforms.LightIntensityUnif, 1.0f, 1.0f, 1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBuffer);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (void*)sizeof(glm::vec3));
    
	glDrawElements(GL_TRIANGLES, ((terrainWidth-1)*(terrainHeight-1)*6), GL_UNSIGNED_INT, resources.indices);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}

void TerrainRenderer::Initialize()
{
	//Set up for rendering, allocate shaders and data

	terrainWidth = 128;
	terrainHeight = 128;

	g_lightDirection = glm::vec4(-100.f, 0.f, -100.0f, 0.0f);

	Shader vs(GL_VERTEX_SHADER);
	vs.Load("data/DirVertexLighting_PN.vert");
	vs.Compile();

	Shader fs(GL_FRAGMENT_SHADER);
	fs.Load("data/ColorPassthrough.frag");
	fs.Compile();

	resources.Program.AttachShader(vs);
	resources.Program.AttachShader(fs);

	resources.Program.Link();

	LoadUniforms();

	glGenBuffers(1, &resources.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBuffer);

	NoiseTerrain2D terrain(terrainWidth, terrainHeight, 10, 6.f, 10.f, 4711);
	terrain.GenerateData();

	VertexPositionNormal* vertices;
	VerticesAndIndicesFromData(terrain.GetData(), terrainWidth, terrainHeight, &vertices, &resources.indices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormal)*terrainWidth*terrainHeight, &(vertices[0].Position), GL_STATIC_DRAW);

	delete[] vertices;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TerrainRenderer::LoadUniforms()
{
	resources.Uniforms.ModelToCameraMatrix = LoadUniform("modelToCameraMatrix");
	resources.Uniforms.NormalModelToCameraMatrixUnif = LoadUniform("normalModelToCameraMatrix"); 
	resources.Uniforms.DirToLightUnif = LoadUniform("dirToLight"); 
	resources.Uniforms.LightIntensityUnif = LoadUniform("lightIntensity"); 
	resources.Uniforms.CameraToClipMatrix = LoadUniform("cameraToClipMatrix");
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
