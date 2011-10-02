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

const glm::vec3* TrianglesFromDataGLM(const float* data, int width, int height)
{
	int nrTriangles = (width-1)*(height-1);
	glm::vec3* vertices = new glm::vec3[nrTriangles*3];

	float wOffset = width/2.f;
	float hOffset = height/2.f; 

	int triangles = 0;
	for(int i=0; i < width-1; i++) 
	{
		for(int j=0; j < height-1; j++)
		{
			int offset = j + i * height;
			vertices[triangles].x = i - wOffset;
			vertices[triangles].y = j - hOffset;
			vertices[triangles].z = data[offset];

			triangles++;

			offset = j + (i+1) * height;
			vertices[triangles].x = i + 1 - wOffset;
			vertices[triangles].y = j - hOffset;
			vertices[triangles].z = data[offset];

			triangles++;

			offset = j + 1 + (i + 1) * height;
			vertices[triangles].x = i + 1 - wOffset;
			vertices[triangles].y = j + 1 - hOffset;
			vertices[triangles].z = data[offset];

			triangles++;
		}
	}
	return vertices;
}

void VerticesAndIndicesFromData(const float* data, int width, int height, VertexPositionNormal** vertices, GLuint** indices)
{
	int nrVertices = width*height;
	(*vertices) = new VertexPositionNormal[nrVertices];

	float wOffset = width/2.f;
	float hOffset = height/2.f;

	for(int i=0; i<width; i++)
	{
		for(int j=0; j<height; j++)
		{
			int dataOffset = j + i * height;
						
			(*vertices)[dataOffset].Position.x = i - wOffset;
			(*vertices)[dataOffset].Position.y = j - hOffset;
			(*vertices)[dataOffset].Position.z = data[dataOffset];
		}
	}

	int nrTriangles = (width-1)*(height-1)*2;
	(*indices) = new GLuint[nrTriangles*3];

	int quadNr = 0;
	for(int i=0; i<width-1; i++)
	{
		for(int j=0; j<height-1; j++)
		{
			GLuint vertexOffset = j + i * height;
			(*indices)[quadNr * 6 + 0] = vertexOffset;
			(*indices)[quadNr * 6 + 3] = vertexOffset;
			
			vertexOffset = j + (i + 1) * height;
			(*indices)[quadNr * 6 + 4] = vertexOffset;

			vertexOffset = j + 1 + (i + 1)*height;
			(*indices)[quadNr * 6 + 1] = vertexOffset;
			(*indices)[quadNr * 6 + 5] = vertexOffset;

			vertexOffset = j + 1 + i * height;
			(*indices)[quadNr * 6 + 2] = vertexOffset;	

			quadNr++;
		}
	}

	for(int i=0; i<nrTriangles*3; i+=3)
	{
		GLuint verticeIndex = (*indices)[i + 0];
		glm::vec3 a = (*vertices)[(*indices)[i + 0]].Position;
		glm::vec3 b = (*vertices)[(*indices)[i + 1]].Position;
		glm::vec3 c = (*vertices)[(*indices)[i + 2]].Position;

		glm::vec3 normal = glm::normalize(glm::cross(c - a, b - a));

		(*vertices)[(*indices)[i + 0]].Normal += normal;
		(*vertices)[(*indices)[i + 1]].Normal += normal;
		(*vertices)[(*indices)[i + 2]].Normal += normal;
	}

	for(int i=0; i < nrVertices; i++) 
	{
		(*vertices)[i].Normal = glm::normalize((*vertices)[i].Normal);
	}
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