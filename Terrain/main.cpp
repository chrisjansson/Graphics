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


const float vertexPositions[] = {
    0.75f, 0.75f, 0.0f, 1.0f,
    0.75f, -0.75f, 0.0f, 1.0f,
    -0.75f, -0.75f, 0.0f, 1.0f,
};

GLuint bufferObject;

void InitializeBufferObject()
{
	glewInit();

	glGenBuffers(1, &bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	NoiseTerrain2D terrain(128, 128, 10, 4.f, 5.f, 4711);
	terrain.GenerateData();
	const float* vertices = LinesFromData(terrain.GetData(), 128, 128);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(128*127*2)*6, vertices, GL_STATIC_DRAW);
}

void Render() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(200, 64, 50, 64, 64, 0, 0, 0, 1);

	//glTranslatef(-64, -64, 0);

	//glTranslatef(0.f, 0.f, -400.f);

	glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_LINES, 0, (128*127*2)*2);

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

//void InitializeVertexBuffer()
//{
//	NoiseTerrain2D terrain(1024, 1024, 10, 4.f, 1.f, 4711);
//	terrain.GenerateData();
//	const float* vertices = LinesFromData(terrain.GetData(), 1024, 1024);
//
//	glGenBuffers(1, &positionBufferObject);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

int main(int argc, char** argv) 
{
	sf::WindowSettings settings;
	settings.DepthBits         = 24; // Request a 24 bits depth buffer
	settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing
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

		app.Display();
	}

	glDeleteBuffers(1, &bufferObject);

	return 0;
}