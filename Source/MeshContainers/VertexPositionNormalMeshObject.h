#ifndef VERTEX_POSITION_NORMAL_MESH_OBJECT
#define VERTEX_POSITION_NORMAL_MESH_OBJECT

#include "VerticesFromDataGenerator.h"
#include <gl/glew.h>

class VertexPositionNormalMeshObject
{
public:
	VertexPositionNormalMeshObject(const VertexPositionNormal* vertices, int count);
	void Draw();
	~VertexPositionNormalMeshObject();
private:
	GLuint _vertexArrayObject;
	GLuint _vertexBufferObject;
	int _count;
	void SetVertexAttributePointers();
};

#endif