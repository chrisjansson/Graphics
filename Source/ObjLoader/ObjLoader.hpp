#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "DataStore/DataStore.hpp"
#include "TypeParser/TypeParsers.hpp"

#include <string>
#include <iostream>
#include <vector>

struct DataCount
{
	DataCount() : Vertices(0), Normals(0), VertexTextures(0), Faces(0) {}

	int Vertices;
	int Normals;
	int VertexTextures;
	int Faces;
};

class ObjLoader
{
public:
	ObjLoader(DataStore &dataStore);

	void Parse(std::istream &lineStream);
	void RewindStream( std::istream &lineStream );

private:
	DataStore _dataStore;
	VertexParser _vertexParser;
	NormalParser _normalParser;
	TextureParser _textureParser;

	std::vector<ITypeParser*> _parsers;

	DataCount _dataCount; 

	void CountData(std::istream &stream);
	void CountKeyWord( std::string keyWord );
	void AllocateData();
};

#endif