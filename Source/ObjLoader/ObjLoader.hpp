#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "DataStore/DataStore.hpp"
#include "TypeParser/TypeParsers.hpp"

#include <string>
#include <iostream>
#include <vector>

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
	FaceParser _faceParser;

	std::vector<ITypeParser*> _parsers;

	void CountData(std::istream &stream);
	void CountKeyWord( std::string keyWord );
	void AllocateData();
};

#endif