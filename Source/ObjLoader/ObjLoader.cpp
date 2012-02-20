#include "ObjLoader.hpp"

void ObjLoader::Parse(std::istream &lineStream)
{
	CountData(lineStream);

	lineStream.clear();           
	lineStream.seekg(0, std::ios::beg);


}

void ObjLoader::CountData(std::istream &stream)
{
	std::string	currentLine;
	
	int v=0, n=0, vt=0, f=0;

	while(stream.good()) 
	{
		std::getline(stream, currentLine);

		std::stringstream lineStream(currentLine);

		std::string keyWord;
		lineStream >> keyWord;

		if(keyWord == "v")
		{
			v++;
		}
		else if(keyWord == "vn") 
		{
			n++;
		}
		else if(keyWord == "vt")
		{
			vt++;
		}
		else if(keyWord == "f") 
		{
			f++;
		}
		else if(keyWord == "#")
		{

		}
	}
}

ObjLoader::ObjLoader(DataStore &dataStore) : _dataStore(dataStore), _vertexParser(dataStore), _normalParser(dataStore), _textureParser(dataStore)
{
}
