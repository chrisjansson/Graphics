#include "VerticesFromDataGenerator.h"
#include "VertexAttribute.h"
#include "MeshObject.h"

glm::vec3 n0 = glm::vec3(1.f, 0.f, 0.f);
glm::vec3 n1 = glm::vec3(-1.f, 0.f, 0.f);
glm::vec3 n2 = glm::vec3(0.f, 1.f, 0.f);
glm::vec3 n3 = glm::vec3(0.f, -1.f, 0.f);
glm::vec3 n4 = glm::vec3(0.f, 0.f, 1.f);
glm::vec3 n5 = glm::vec3(0.f, 0.f, -1.f);

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
}

void SetFrontData()
{
	vertices[0].Position = p0;
	vertices[0].Normal = n5;

	vertices[1].Position = p2;
	vertices[1].Normal = n5;

	vertices[2].Position = p1;
	vertices[2].Normal = n5;

	vertices[3].Position = p0;
	vertices[3].Normal = n5;

	vertices[4].Position = p3;
	vertices[4].Normal = n5;

	vertices[5].Position = p2;
	vertices[5].Normal = n5;
}

void SetBackData()
{
	vertices[6].Position = p4;
	vertices[6].Normal = n4;

	vertices[7].Position = p5;
	vertices[7].Normal = n4;

	vertices[8].Position = p6;
	vertices[8].Normal = n4;

	vertices[9].Position = p4;
	vertices[9].Normal = n4;

	vertices[10].Position = p6;
	vertices[10].Normal = n4;

	vertices[11].Position = p7;
	vertices[11].Normal = n4;
}

void SetTopData()
{
	vertices[12].Position = p3;
	vertices[12].Normal = n2;

	vertices[13].Position = p6;
	vertices[13].Normal = n2;

	vertices[14].Position = p2;
	vertices[14].Normal = n2;

	vertices[15].Position = p3;
	vertices[15].Normal = n2;

	vertices[16].Position = p7;
	vertices[16].Normal = n2;

	vertices[17].Position = p6;
	vertices[17].Normal = n2;
}

void SetBottomData()
{
	vertices[18].Position = p4;
	vertices[18].Normal = n3;

	vertices[19].Position = p1;
	vertices[19].Normal = n3;

	vertices[20].Position = p5;
	vertices[20].Normal = n3;

	vertices[21].Position = p4;
	vertices[21].Normal = n3;

	vertices[22].Position = p0;
	vertices[22].Normal = n3;

	vertices[23].Position = p1;
	vertices[23].Normal = n3;
}

void SetLeftData()
{
	vertices[24].Position = p4;
	vertices[24].Normal = n1;

	vertices[25].Position = p3;
	vertices[25].Normal = n1;
	
	vertices[26].Position = p0;
	vertices[26].Normal = n1;

	vertices[27].Position = p4;
	vertices[27].Normal = n1;

	vertices[28].Position = p7;
	vertices[28].Normal = n1;

	vertices[29].Position = p3;
	vertices[29].Normal = n1;
}

void SetRightData()
{
	vertices[30].Position = p1;
	vertices[30].Normal = n0;

	vertices[31].Position = p6;
	vertices[31].Normal = n0;

	vertices[32].Position = p5;
	vertices[32].Normal = n0;

	vertices[33].Position = p1;
	vertices[33].Normal = n0;

	vertices[34].Position = p2;
	vertices[34].Normal = n0;

	vertices[35].Position = p6;
	vertices[35].Normal = n0;
}

//front face
