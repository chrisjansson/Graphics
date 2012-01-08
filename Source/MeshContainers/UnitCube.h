#ifndef UNIT_CUBE_H
#define UNIT_CUBE_H

#include "VertexPositionNormalMeshObject.h"
#include "VerticesFromDataGenerator.h"



class UnitCube
{
public:
	UnitCube();
	~UnitCube();

	void Draw();
private:
	VertexPositionNormalMeshObject *_mesh;

	void SetCubeData( VertexPositionNormal * vertices );
	void CalculateNormals( VertexPositionNormal * vertices );
	void SetRightVertices( VertexPositionNormal * vertices );
	void SetLeftVertices( VertexPositionNormal * vertices );
	void SetBottomVertices( VertexPositionNormal * vertices );
	void SetTopVertices( VertexPositionNormal * vertices );
	void SetBackVertices( VertexPositionNormal * vertices );
	void SetFrontVertices( VertexPositionNormal * vertices );
};


#endif