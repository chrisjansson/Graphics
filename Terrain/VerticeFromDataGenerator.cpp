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

			vertices[lineOffset + 0] = (float)(i - width/2);
			vertices[lineOffset + 1] = (float)(j - height/2);
			vertices[lineOffset + 2] = data[offset];

			offset = j + (i+1) * height;
			vertices[lineOffset + 3] = (float)(i + 1 - width/2);
			vertices[lineOffset + 4] = (float)(j - height/2);
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

			vertices[lineOffset + 0] = (float)(i - width/2);
			vertices[lineOffset + 1] = (float)(j - height/2);
			vertices[lineOffset + 2] = data[offset];

			offset = (j + 1) + i * height;
			vertices[lineOffset + 3] = (float)(i - width/2);
			vertices[lineOffset + 4] = (float)(j + 1 - height/2);
			vertices[lineOffset + 5] = data[offset];
			lineNr++;
		}
	}

	return vertices;
}

const float* TrianglesFromData(const float* data, int width, int height)
{
	int nrQuads = (width - 1)*(height - 1);
	float* vertices = new float[nrQuads*9];

	float wOffset = width/2.f;
	float hOffset = height/2.f;


	int nrTriangles = 0;
	for(int i=0; i<width-1; i++)
	{
		for(int j=0; j<height-1; j++)
		{
			float x1,y1,z1;
			int offset = j + i * height;
			x1 = (i - wOffset);
			y1 = (j - hOffset);
			z1 = data[offset];

			float x2,y2,z2;
			offset = j + (i+1) * height;
			x2 = (i + 1 - wOffset);
			y2 = (j - hOffset);
			z2 = data[offset];

			float x3, y3, z3;
			offset = j + 1 + (i + 1) * height;
			x3 = (i + 1 - wOffset);
			y3 = (j + 1 - hOffset);
			z3 = data[offset];

			int triangleOffset = nrTriangles * 9;

			vertices[triangleOffset + 0] = x1;
			vertices[triangleOffset + 1] = y1;
			vertices[triangleOffset + 2] = z1;

			vertices[triangleOffset + 3] = x2;
			vertices[triangleOffset + 4] = y2;
			vertices[triangleOffset + 5] = z2;

			vertices[triangleOffset + 6] = x3;
			vertices[triangleOffset + 7] = y3;
			vertices[triangleOffset + 8] = z3;

			nrTriangles++;
		}
	}

	return vertices;
}