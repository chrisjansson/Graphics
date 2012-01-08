#include "UnitCube.h"

glm::vec3 cubeVertices[] = { 
	glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), //Front
	glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f) //Back
};

UnitCube::UnitCube()
{
	VertexPositionNormal vertices[36];

	SetCubeData(vertices);

	_mesh = new VertexPositionNormalMeshObject(vertices, 36);
}

UnitCube::~UnitCube()
{
	delete _mesh;
	_mesh = NULL;
}


void UnitCube::Draw()
{
	_mesh->Draw();
}

void UnitCube::SetFrontVertices( VertexPositionNormal * vertices )
{
	//Front
	vertices[0].Position = cubeVertices[0];
	vertices[1].Position = cubeVertices[2];
	vertices[2].Position = cubeVertices[1];

	vertices[3].Position = cubeVertices[0];
	vertices[4].Position = cubeVertices[3];
	vertices[5].Position = cubeVertices[2];
}

void UnitCube::SetTopVertices( VertexPositionNormal * vertices )
{
	//Top
	vertices[12].Position = cubeVertices[3];
	vertices[13].Position = cubeVertices[6];
	vertices[14].Position = cubeVertices[2];

	vertices[15].Position = cubeVertices[3];
	vertices[16].Position = cubeVertices[7];
	vertices[17].Position = cubeVertices[6];
}

void UnitCube::SetBackVertices( VertexPositionNormal * vertices )
{
	//Back
	vertices[6].Position = cubeVertices[4];
	vertices[7].Position = cubeVertices[5];
	vertices[8].Position = cubeVertices[6];

	vertices[9].Position = cubeVertices[4];
	vertices[10].Position = cubeVertices[6];
	vertices[11].Position = cubeVertices[7];
}

void UnitCube::SetBottomVertices( VertexPositionNormal * vertices )
{
	//Bottom
	vertices[18].Position = cubeVertices[4];
	vertices[19].Position = cubeVertices[1];
	vertices[20].Position = cubeVertices[5];

	vertices[21].Position = cubeVertices[4];
	vertices[22].Position = cubeVertices[0];
	vertices[23].Position = cubeVertices[1];
}

void UnitCube::SetLeftVertices( VertexPositionNormal * vertices )
{
	//Left
	vertices[24].Position = cubeVertices[4];
	vertices[25].Position = cubeVertices[3];
	vertices[26].Position = cubeVertices[0];

	vertices[27].Position = cubeVertices[4];
	vertices[28].Position = cubeVertices[7];
	vertices[29].Position = cubeVertices[3];
}

void UnitCube::SetRightVertices( VertexPositionNormal * vertices )
{
	//Right
	vertices[30].Position = cubeVertices[1];
	vertices[31].Position = cubeVertices[6];
	vertices[32].Position = cubeVertices[5];

	vertices[33].Position = cubeVertices[1];
	vertices[34].Position = cubeVertices[2];
	vertices[35].Position = cubeVertices[6];
}

void UnitCube::CalculateNormals( VertexPositionNormal * vertices )
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

void UnitCube::SetCubeData( VertexPositionNormal * vertices )
{
	SetFrontVertices(vertices);
	SetBackVertices(vertices);
	SetTopVertices(vertices);
	SetBottomVertices(vertices);
	SetLeftVertices(vertices);
	SetRightVertices(vertices);

	CalculateNormals(vertices);
}






