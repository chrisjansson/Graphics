#ifndef DATA_STORE_H
#define DATA_STORE_H

#include <GLM/glm.hpp>

typedef glm::detail::tvec3<float> Normal;
typedef glm::detail::tvec3<float> Vertex;
typedef glm::detail::tvec2<float> Texture;

class DataStore 
{
public:
	DataStore();
	~DataStore();
	
	void Initalize(int vertices, int normals, int textures);

	void AllocateSpaceForNormals(int count);
	void AllocateSpaceForVertices(int count);
	void AllocateSpaceForTextures(int count);
	void AllocateSpaceForFaces(int count);

	void AddNormal(Normal normal);
	Normal GetNormal(int i);

	void AddVertex(Vertex vertex);
	Vertex GetVertex(int i);

	void AddTexture(Texture texture);
	Texture GetTexture(int i);

private:
	int _numberOfVertices;
	int _verticeIndex;
	Vertex *_vertices;

	int _numberOfNormals;
	int _normalIndex;
	Normal *_normals;

	int _numberOfTextures;
	int _textureIndex;
	Texture *_textures;
};

#endif