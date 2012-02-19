#ifndef VERTEX_PARSER
#define VERTEX_PARSER

#include "ITypeParser.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class VertexParser : ITypeParser
{
public:
	VertexParser(DataStore &dataStore);

	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &line);

private:
	DataStore &_dataStore;
};

#endif