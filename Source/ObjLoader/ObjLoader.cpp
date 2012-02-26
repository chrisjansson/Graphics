#include "ObjLoader.hpp"

void ObjLoader::Parse(std::istream &lineStream)
{
	CountData(lineStream);

	AllocateData();

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
	for (int i = 0; i < _parsers.size(); i++)
	{
		_parsers[i]->CountKeyword(keyWord);
	}
}

void ObjLoader::RewindStream( std::istream &lineStream )
{
	lineStream.clear();           
	lineStream.seekg(0, std::ios::beg);
}

ObjLoader::ObjLoader(DataStore &dataStore) : _dataStore(dataStore), _vertexParser(dataStore), _normalParser(dataStore), _textureParser(dataStore)
{
	_parsers.push_back(&_vertexParser);
	_parsers.push_back(&_normalParser);
	_parsers.push_back(&_textureParser);
}

void ObjLoader::AllocateData()
{
	for (int i = 0; i < _parsers.size(); i++)
	{
		_parsers[i]->AllocateSpace();
	}
}




