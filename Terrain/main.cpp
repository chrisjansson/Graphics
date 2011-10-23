#include <GL\glew.h>
#include <iostream>
#include <SFML/window.hpp>
#include "NoiseTerrain.h"
#include "VerticesFromDataGenerator.h"

#include "Shader.h"
#include "Program.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer\BaseRenderer.h"

void ReSize(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projectionMatrix = glm::perspective(50.0f, (float)width/(float)height, 1.f, 500.f);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));
}

GLuint bufferObject;
GLuint* indices;

int width2 = 128;
int height2 = 128;

void InitializeBufferObject()
{
	glewInit();

	glGenBuffers(1, &bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	NoiseTerrain2D terrain(width2, height2, 10, 6.f, 10.f, 4711);
	terrain.GenerateData();

	VertexPositionNormal* vertices;
	VerticesAndIndicesFromData(terrain.GetData(), width2, height2, &vertices, &indices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormal)*width2*height2, &(vertices[0].Position), GL_STATIC_DRAW);

	delete[] vertices;
}

sf::Clock clockObject;
	
Program* program;
void LoadShaders()
{
	Shader vs(GL_VERTEX_SHADER);
	vs.Load("data/DirVertexLighting_PN.vert");
	vs.Compile();

	Shader fs(GL_FRAGMENT_SHADER);
	fs.Load("data/ColorPassthrough.frag");
	fs.Compile();

	program = new Program();

	program->AttachShader(vs);
	program->AttachShader(fs);

	program->Link();
}

glm::vec4 g_lightDirection(-100.f, 0.f, -100.0f, 0.0f);

GLuint dirToLightUnif;
GLuint modelToCameraMatrixUnif;
GLuint normalModelToCameraMatrixUnif;
GLuint lightIntensityUnif;

GLuint g_projectionUniformBuffer = 0;

struct ProjectionBlock
{
	glm::mat4 cameraToClipMatrix;
};

void ReSize2(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projectionMatrix = glm::perspective(50.0f, (float)width/(float)height, 1.f, 500.f);

	//glm::mat4 projectionMatrix = glm::ortho(-128.f, 128.f, -10.f, 10.f, 1.f, 500.f);

	ProjectionBlock projData;
	projData.cameraToClipMatrix = projectionMatrix;

	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ProjectionBlock), &projData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GetUniformLocations()
{
	modelToCameraMatrixUnif = glGetUniformLocation(program->GetProgram(), "modelToCameraMatrix");
	normalModelToCameraMatrixUnif = glGetUniformLocation(program->GetProgram(), "normalModelToCameraMatrix");
	dirToLightUnif = glGetUniformLocation(program->GetProgram(), "dirToLight");
	lightIntensityUnif = glGetUniformLocation(program->GetProgram(), "lightIntensity");

	GLuint projectionBlock = glGetUniformBlockIndex(program->GetProgram(), "Projection");
	glUniformBlockBinding(program->GetProgram(), projectionBlock, 2);
}

void Render2() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 modelViewMatrix = glm::lookAt(glm::vec3(0.f, 100.f, 50.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 rotationMatrix = glm::rotate(modelViewMatrix, clockObject.GetElapsedTime()*10, glm::vec3(0.f, 0.f, 1.f));

	glm::vec4 lightDirCameraSpace = glm::normalize(modelViewMatrix * g_lightDirection);
    
	program->Use();

	glUniform3fv(dirToLightUnif, 1, glm::value_ptr(lightDirCameraSpace));
	glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glm::mat3 normMatrix(rotationMatrix);
	glUniformMatrix3fv(normalModelToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
	glUniform4f(lightIntensityUnif, 1.0f, 1.0f, 1.0f, 1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (void*)sizeof(glm::vec3));
    
	glDrawElements(GL_TRIANGLES, ((width2-1)*(height2-1)*6), GL_UNSIGNED_INT, indices);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}

void Render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);

	glm::mat4 modelViewMatrix = glm::lookAt(glm::vec3(0.f, 100.f, 100.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 rotationMatrix = glm::rotate(modelViewMatrix, clockObject.GetElapsedTime()*10, glm::vec3(0.f, 0.f, 1.f));

	glLoadMatrixf(glm::value_ptr(rotationMatrix));

	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);

	glDrawElements(GL_TRIANGLES, (127*127*6), GL_UNSIGNED_INT, indices);

	glDisableVertexAttribArray(0);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void Init()
{
	// Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

	InitializeBufferObject();

	LoadShaders();
	GetUniformLocations();

	glGenBuffers(1, &g_projectionUniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, g_projectionUniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ProjectionBlock), NULL, GL_DYNAMIC_DRAW);

	//Bind the static buffers.
	glBindBufferRange(GL_UNIFORM_BUFFER, 2, g_projectionUniformBuffer, 0, sizeof(ProjectionBlock));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	ReSize2(800, 600);
}

float oldTime=0;
int frames=0;
void PrintFPS()
{
	float time = clockObject.GetElapsedTime();
	float dT = time - oldTime;
	
	if(dT > 1)
	{
		std::cout << frames << std::endl;
		oldTime = time;
		frames = 0;
	} 
	else 
	{
		frames++;
	}
}

int main(int argc, char** argv) 
{
	sf::WindowSettings settings;
	settings.DepthBits         = 32; // Request a 24 bits depth buffer
	settings.StencilBits       = 0;  // Request a 8 bits stencil buffer
	settings.AntialiasingLevel = 0;  // Request 2 levels of antialiasing
	sf::Window app(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Resize, settings);
	
	Init();

	BaseRenderer b;
	b.ReSize(100, 100);

	fprintf(stderr, "Hello stderr world!");

	while(app.IsOpened()) 
	{
		sf::Event event;
		while(app.GetEvent(event)) 
		{
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                app.Close();

            // Escape key : exit
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
                app.Close();

			if (event.Type == sf::Event::Resized)
				ReSize2(event.Size.Width, event.Size.Height);
		}
		app.SetActive();

		Render2();

		PrintFPS();

		app.Display();
	}

	glDeleteBuffers(1, &bufferObject);

	return 0;
}