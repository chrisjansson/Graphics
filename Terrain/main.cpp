#include <iostream>
#include <GL\glew.h>
#include <SFML/window.hpp>
#include "NoiseTerrain.h"
#include "VerticesFromDataGenerator.h"

void ReSize(int width, int height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (50.0, (float)width/(float)height, 1.f, 500.f);
}

GLuint bufferObject;

void InitializeBufferObject()
{
	glewInit();

	glGenBuffers(1, &bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	NoiseTerrain2D terrain(128, 128, 10, 4.f, 10.f, 4711);
	terrain.GenerateData();
	/*const float* vertices = LinesFromData(terrain.GetData(), 128, 128);*/
	const float* vertices = TrianglesFromData(terrain.GetData(), 128, 128);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(128*127*2)*6, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(127*127)*9, vertices, GL_STATIC_DRAW);

	delete[] vertices;
}

sf::Clock clockObject;

void Render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 100, 100, 0, 1, 0, 0, 0, 1);
	
	glRotatef(clockObject.GetElapsedTime()*10, 0.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDrawArrays(GL_LINES, 0, (128*127*2)*2);
	glDrawArrays(GL_TRIANGLES, 0, 127*127*4);

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
}

float oldTime=0;
int frames=0;
void PrintFPS()
{
	float time = clockObject.GetElapsedTime();
	float dT = time - oldTime;
	frames++;
	if(dT > 1)
	{
		std::cout << frames << std::endl;
		oldTime = time;
		frames = 0;
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