#ifndef VERTEX_PARSER
#define VERTEX_PARSER

#include "TypeParserBase.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class VertexParser : public TypeParserBase
{
public:
	VertexParser(DataStore &dataStore);

	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &line);
	void AllocateSpace();
};

#endif