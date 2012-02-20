#include "ObjLoader.hpp"

void ObjLoader::Parse(std::istream &lineStream)
{
	CountData(lineStream);

	_dataStore.Initalize(_dataCount.Vertices, _dataCount.Normals, _dataCount.VertexTextures);

	RewindStream(lineStream);
}

void ObjLoader::CountData(std::istream &stream)
{
	std::string	currentLine;

	while(stream.good()) 
	{
		std::getline(stream, currentLine);

		std::stringstream lineStream(currentLine);

		std::string keyWord;
		lineStream >> keyWord;

		CountKeyWord(keyWord);
	}
}

void ObjLoader::CountKeyWord(std::string keyWord)
{
	//Possibly just a list of parsers and use can parse?
	if(keyWord == "v")
	{
		_dataCount.Vertices++;
	}
	else if(keyWord == "f") 
	{
		_dataCount.Faces++;
	}
	else if(keyWord == "vn") 
	{
		_dataCount.Normals++;
	}
	else if(keyWord == "vt")
	{
		_dataCount.VertexTextures++;
	}
	else if(keyWord == "#")
	{

	}
}

void ObjLoader::RewindStream( std::istream &lineStream )
{
	lineStream.clear();           
	lineStream.seekg(0, std::ios::beg);
}

ObjLoader::ObjLoader(DataStore &dataStore) : _dataStore(dataStore), _vertexParser(dataStore), _normalParser(dataStore), _textureParser(dataStore)
{
}




