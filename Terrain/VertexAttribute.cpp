#include "VertexAttribute.h"

void CreateVertexArrayObject(VertexPositionNormal const *vertices, GLuint *vertexArrayObject, GLuint *vertexBufferObject, int count)
{
	glGenVertexArrays(1, vertexArrayObject);
	glBindVertexArray(*vertexArrayObject);

	glGenBuffers(1, vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObject);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormal)*count, &(vertices[0].Position), GL_STATIC_DRAW);
	
	SetVertexAttributePointers();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SetVertexAttributePointers() 
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormal), (void*)sizeof(glm::vec3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}


