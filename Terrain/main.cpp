#include <GL\glew.h>
#include <iostream>
#include <SFML/window.hpp>

#include "Renderer\BaseRenderer.h"
#include "Renderer\TerrainRenderer\TerrainRenderer.h"

sf::Clock clockObject;

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
	
	glewInit();

	ProjectionSettings projectionSettings;
	TerrainRenderer terrainRenderer(projectionSettings);
	terrainRenderer.Initialize();
	terrainRenderer.ReSize(800, 600);

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
				terrainRenderer.ReSize(event.Size.Width, event.Size.Height);
		}
		app.SetActive();

		terrainRenderer.Render();

		PrintFPS();

		app.Display();
	}

	return 0;
}