#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

#include <gl/glew.h>
#include "VerticesFromDataGenerator.h"

#define POSITION_ATTRIBUTE_LOCATION 0
#define NORMAL_ATTRIBUTE_LOCATION 1

void SetVertexAttributePointers();
void CreateVertexArrayObject(VertexPositionNormal const *vertices, GLuint *vertexArrayObject, GLuint *vertexBufferObject, int count);
#endif