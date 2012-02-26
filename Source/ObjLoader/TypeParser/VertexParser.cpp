#include "VertexParser.hpp"

void VertexParser::ParseLine(const std::string &line)
{
	std::stringstream lineStream;
	lineStream.str(line);

	float x, y, z;
	lineStream >> x >> y >> z;

	Vertex v(x, y, z);
	_dataStore.AddVertex(v);
}

bool VertexParser::CanParseLine(const std::string &keyWord)
{
	return keyWord.compare("v") == 0;
}

VertexParser::VertexParser(DataStore &dataStore) : _dataStore(dataStore)
{
	
}

void VertexParser::AllocateSpace()
{
	_dataStore.AllocateSpaceForVertices(_count);
}
