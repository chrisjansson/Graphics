#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "DataStore/DataStore.hpp"
#include "TypeParser/TypeParsers.hpp"

#include <string>
#include <iostream>

class ObjLoader
{
public:
	ObjLoader(DataStore &dataStore);

	void Parse(std::istream &lineStream);
private:
	DataStore _dataStore;
	VertexParser _vertexParser;
	NormalParser _normalParser;
	TextureParser _textureParser;

	void CountData(std::istream &stream);
};

#endif