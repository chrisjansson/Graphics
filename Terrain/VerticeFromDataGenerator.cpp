#include "VerticesFromDataGenerator.h"

const float* PointsFromData(const float* data, int width, int height) 
{
	int nrPoints = width*height;
	float* vertices = new float[nrPoints*3];

	int pointNr = 0;
	for(int i=0; i < width; i++) 
	{
		for(int j=0; j < height; j++)
		{
			int offset = j + i * height;
			int pointOffset = pointNr * 3;

			vertices[pointOffset + 0] = (float)i;
			vertices[pointOffset + 1] = (float)j;
			vertices[pointOffset + 2] = data[offset];

			pointNr++;
		}
	}

	return vertices;
}

const float* LinesFromData(const float* data, int width, int height) 
{
	int nrLines = (width-1) * (height) + width*(height-1);
	float* vertices = new float[nrLines*6];

	int lineNr = 0;
	for(int i=0; i < width - 1; i++)
	{
		for(int j=0; j < height; j++)
		{
			int offset = j + i * height;
			int lineOffset = lineNr * 6;

			vertices[lineOffset + 0] = (float)i;
			vertices[lineOffset + 1] = (float)j;
			vertices[lineOffset + 2] = data[offset];

			offset = j + (i+1) * height;
			vertices[lineOffset + 3] = (float)(i + 1);
			vertices[lineOffset + 4] = (float)j;
			vertices[lineOffset + 5] = data[offset];
			lineNr++;
		}
	}

	for(int i=0; i < width; i++) 
	{
		for(int j=0; j < height - 1; j++)
		{
			int offset = j + i * height;
			int lineOffset = lineNr * 6;

			vertices[lineOffset + 0] = (float)i;
			vertices[lineOffset + 1] = (float)j;
			vertices[lineOffset + 2] = data[offset];

			offset = (j + 1) + i * height;
			vertices[lineOffset + 3] = (float)i;
			vertices[lineOffset + 4] = (float)(j + 1);
			vertices[lineOffset + 5] = data[offset];
			lineNr++;
		}
	}

	return vertices;
}