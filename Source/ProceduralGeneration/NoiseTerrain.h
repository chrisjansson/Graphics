#include "noise\perlin.h"

class NoiseTerrain2D
{
public:
	NoiseTerrain2D(int width, int height, int octaves, float freq, float amp, int seed);
	~NoiseTerrain2D();
	void GenerateData();

	const float * GetData() 
	{
		return this->data;
	};

private:
	float* data;
	int width;
	int height;
	int octaves;
	int seed;
	float freq;
	float amp;
};