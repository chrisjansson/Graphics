#include "DataStore.hpp"

//TODO: Assert that array addition is within bounds
void DataStore::AddNormal(Normal normal)
{
	_normals[_normalIndex++] = normal;
}

Normal DataStore::GetNormal(int i)
{
	return _normals[i];
}

void DataStore::AddVertex(Vertex vertex)
{
	_vertices[_verticeIndex++] = vertex;
}

Vertex DataStore::GetVertex(int i)
{
	return _vertices[i];
}

void DataStore::AddTexture(Texture texture)
{
	_textures[_textureIndex++] = texture;
}

Texture DataStore::GetTexture(int i)
{
	return _textures[i];
}

DataStore::DataStore()  : 
	_numberOfVertices(0), 
	_verticeIndex(0), 
	_numberOfNormals(0), 
	_normalIndex(0), 
	_numberOfTextures(0), 
	_textureIndex(0),
	_vertices(NULL),
	_normals(NULL),
	_textures(NULL)
{
}

DataStore::~DataStore()
{
	delete[] _vertices;
	delete[] _normals;
	delete[] _textures;
}

void DataStore::AllocateSpaceForNormals(int count)
{
	_numberOfNormals = count;
	_normals = new Normal[count];
}

void DataStore::AllocateSpaceForVertices(int count)
{
	_numberOfVertices = count;
	_vertices = new Vertex[count];
}

void DataStore::AllocateSpaceForTextures(int count)
{
	_numberOfTextures = count;
	_textures = new Texture[count];
}





