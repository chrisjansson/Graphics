#include <GL\glew.h>
#include <iostream>
#include <SFML/window.hpp>

#include "Renderer\BaseRenderer.h"
#include "Renderer\TerrainRenderer\TerrainRenderer.h"

sf::Clock clockObject;

float oldTime=0;
float startTime;
int frames=0;
void PrintFPS()
{
	sf::Time time = clockObject.GetElapsedTime();
	float dT = time.AsSeconds() - oldTime;
	
	if(dT > 1)
	{
		std::cout << frames << std::endl;
		oldTime = time.AsSeconds();
		frames = 0;
	} 
	else 
	{
		frames++;
	}
}

int main(int argc, char** argv) 
{
	sf::ContextSettings settings;
	settings.DepthBits         = 32; // Request a 24 bits depth buffer
	settings.StencilBits       = 0;  // Request a 8 bits stencil buffer
	settings.AntialiasingLevel = 0;  // Request 2 levels of antialiasing
	sf::Window app(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Resize, settings);
	
	glewInit();

	ProjectionSettings projectionSettings;
	TerrainRenderer terrainRenderer(projectionSettings);
	terrainRenderer.Initialize();
	terrainRenderer.ReSize(800, 600);

	sf::Clock clock = sf::Clock();

	while(app.IsOpen()) 
	{
		sf::Event event;
		while(app.PollEvent(event)) 
		{
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                app.Close();

            // Escape key : exit
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::Escape))
                app.Close();

			if (event.Type == sf::Event::Resized)
				terrainRenderer.ReSize(event.Size.Width, event.Size.Height);
		}
		app.SetActive();

		sf::Time dT = clock.GetElapsedTime();
		terrainRenderer.Render(dT.AsSeconds());

		app.Display();

		PrintFPS();
	}

	return 0;
}