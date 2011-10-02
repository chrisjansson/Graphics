#include <GL\glew.h>
#include <iostream>
#include <SFML/window.hpp>
#include "NoiseTerrain.h"
#include "VerticesFromDataGenerator.h"
#include "ShaderCompiler.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void loadShaders() 
{
	std::string vertexShaderString = LoadShaderStringFromFile("data/VertexColors.vert");
	std::string fragmentShaderString = LoadShaderStringFromFile("data/VertexColors.frag");

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderString.c_str());
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderString.c_str());

	std::vector<GLuint> shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);

	CreateProgram(shaders);
}

void ReSize(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);

	glm::mat4 projectionMatrix = glm::perspective(50.0f, (float)width/(float)height, 1.f, 500.f);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));
}

GLuint bufferObject;
GLuint* indices;

void InitializeBufferObject()
{
	glewInit();

	glGenBuffers(1, &bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	NoiseTerrain2D terrain(128, 128, 10, 4.f, 10.f, 4711);
	terrain.GenerateData();
	/*const float* vertices = LinesFromData(terrain.GetData(), 128, 128);*/
	//const float* vertices = TrianglesFromData(terrain.GetData(), 128, 128);
	//const glm::vec3* vertices = TrianglesFromDataGLM(terrain.GetData(), 128, 128);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*(128-1)*(128-1)*3, &vertices[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(128*127*2)*6, vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(127*127)*9, vertices, GL_STATIC_DRAW);

	VertexPositionNormal* vertices;

	VerticesAndIndicesFromData(terrain.GetData(), 128, 128, &vertices, &indices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormal)*128*128, &(vertices[0].Position), GL_STATIC_DRAW);

	delete[] vertices;
}

sf::Clock clockObject;

GLuint program;
void LoadShaders()
{
	std::string vertexShaderString = LoadShaderStringFromFile("data/DirVertexLighting_PN.vert");
	std::string fragmentShaderString = LoadShaderStringFromFile("data/ColorPassthrough.frag");

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderString.c_str());
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderString.c_str());

	std::vector<GLuint> shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);

	program = CreateProgram(shaders);
}

void Render2() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
	glUseProgram(program);
    
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (void*)sizeof(glm::vec3));
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
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

	//glDrawArrays(GL_LINES, 0, (128*127*2)*2);
	//glDrawArrays(GL_TRIANGLES, 0, 127*127*4);
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

	ReSize(800, 600);

	InitializeBufferObject();

	//LoadShaders();
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
				ReSize(event.Size.Width, event.Size.Height);
		}
		app.SetActive();

		Render();

		PrintFPS();

		app.Display();
	}

	glDeleteBuffers(1, &bufferObject);

	return 0;
}