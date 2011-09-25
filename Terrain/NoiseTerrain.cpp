#include "NoiseTerrain.h"
#include <iostream>

NoiseTerrain2D::NoiseTerrain2D(int width, int height, int octaves, float freq, float amp, int seed)
{
	this->width = width;
	this->height = height;
	this->octaves = octaves;
	this->freq = freq;
	this->amp = amp;
	this->seed = seed;
}

NoiseTerrain2D::~NoiseTerrain2D() 
{
	delete[] this->data;
}

void NoiseTerrain2D::GenerateData() 
{
	Perlin noise(this->octaves, this->freq, this->amp, this->seed);
	int width = this->width;
	int height = this->height;

	this->data = new float[width*height];

	for(int i=0; i < width; i++)
	{
		for(int j=0; j < height; j++)
		{
			int offset = j + i * height;
			float val = noise.Get(i/((float)width), j/((float)height));
			data[offset] = val;
		}
	}
}