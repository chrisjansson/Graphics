#include "VertexPositionNormalMeshObject.h"

VertexPositionNormalMeshObject::VertexPositionNormalMeshObject(const VertexPositionNormal* vertices, int count)
{
	_count = count;

	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	glGenBuffers(1, &_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormal)*count, vertices, GL_STATIC_DRAW);

	SetVertexAttributePointers();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexPositionNormalMeshObject::SetVertexAttributePointers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (void*)sizeof(glm::vec3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void VertexPositionNormalMeshObject::Draw()
{
	glBindVertexArray(_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, _count);
	glBindVertexArray(0);
}

VertexPositionNormalMeshObject::~VertexPositionNormalMeshObject()
{
	glDeleteBuffers(1, &_vertexBufferObject);
	glDeleteVertexArrays(1, &_vertexArrayObject);
}


