#include "DataStore.hpp"

//TODO: Assert that array addition is within bounds
void DataStore::AddNormal( Normal normal )
{
	_normals[_normalIndex++] = normal;
}

Normal DataStore::GetNormal( int i )
{
	return _normals[i];
}

void DataStore::AddVertex( Vertex vertex )
{
	_vertices[_verticeIndex++] = vertex;
}

Vertex DataStore::GetVertex( int i )
{
	return _vertices[i];
}

void DataStore::AddTexture( Texture texture )
{
	_textures[_textureIndex++] = texture;
}

Texture DataStore::GetTexture( int i )
{
	return _textures[i];
}


void DataStore::Initalize( int vertices, int normals, int textures )
{
	_vertices = new Vertex[vertices];
	_normals = new Normal[normals];
	_textures = new Texture[textures];
}

DataStore::DataStore()  : _numberOfVertices(0), _verticeIndex(0), _numberOfNormals(0), _normalIndex(0), _numberOfTextures(0), _textureIndex(0)
{

}

DataStore::~DataStore()
{
	delete[] _vertices;
	delete[] _normals;
	delete[] _textures;
}





