#include "VerticesFromDataGenerator.h"
#include "VertexAttribute.h"
#include "MeshObject.h"

//Front face coordinates
glm::vec3 p0 = glm::vec3(-0.5f, -0.5f, -0.5f);
glm::vec3 p1 = glm::vec3(0.5f, -0.5f, -0.5f);
glm::vec3 p2 = glm::vec3(0.5f, 0.5f, -0.5f);
glm::vec3 p3 = glm::vec3(-0.5f, 0.5f, -0.5f);

//Back face coordinates
glm::vec3 p4 = glm::vec3(-0.5f, -0.5f, 0.5f);
glm::vec3 p5 = glm::vec3(0.5f, -0.5f, 0.5f);
glm::vec3 p6 = glm::vec3(0.5f, 0.5f, 0.5f);
glm::vec3 p7 = glm::vec3(-0.5f, 0.5f, 0.5f);

VertexPositionNormal vertices[36];

GLuint cubeVertexArrayObject;
GLuint cubeVertexBufferObject;

void InitUnitCube() 
{
	SetUnitCubeData();	
	CreateVertexArrayObject((VertexPositionNormal*)&vertices, &cubeVertexArrayObject, &cubeVertexBufferObject, 36);
}

void DrawUnitCube()
{
	glBindVertexArray(cubeVertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void SetUnitCubeData()
{
	SetFrontData();
	SetBackData();
	SetTopData();
	SetBottomData();
	SetLeftData();
	SetRightData();

	CalculateNormals();
}

void SetFrontData()
{
	vertices[0].Position = p0;
	vertices[1].Position = p2;
	vertices[2].Position = p1;

	vertices[3].Position = p0;
	vertices[4].Position = p3;
	vertices[5].Position = p2;
}

void SetBackData()
{
	vertices[6].Position = p4;
	vertices[7].Position = p5;
	vertices[8].Position = p6;

	vertices[9].Position = p4;
	vertices[10].Position = p6;
	vertices[11].Position = p7;
}

void SetTopData()
{
	vertices[12].Position = p3;
	vertices[13].Position = p6;
	vertices[14].Position = p2;

	vertices[15].Position = p3;
	vertices[16].Position = p7;
	vertices[17].Position = p6;
}

void SetBottomData()
{
	vertices[18].Position = p4;
	vertices[19].Position = p1;
	vertices[20].Position = p5;

	vertices[21].Position = p4;
	vertices[22].Position = p0;
	vertices[23].Position = p1;
}

void SetLeftData()
{
	vertices[24].Position = p4;
	vertices[25].Position = p3;
	vertices[26].Position = p0;

	vertices[27].Position = p4;
	vertices[28].Position = p7;
	vertices[29].Position = p3;
}

void SetRightData()
{
	vertices[30].Position = p1;
	vertices[31].Position = p6;
	vertices[32].Position = p5;

	vertices[33].Position = p1;
	vertices[34].Position = p2;
	vertices[35].Position = p6;
}

void CalculateNormals()
{
	for (int i = 0; i < 36; i += 3)
	{
		VertexPositionNormal &a = vertices[i + 0];
		VertexPositionNormal &b = vertices[i + 1];
		VertexPositionNormal &c = vertices[i + 2];

		glm::vec3 normal = glm::normalize(glm::cross(b.Position - a.Position, c.Position - a.Position));

		a.Normal = normal;
		b.Normal = normal;
		c.Normal = normal;
	}
}
