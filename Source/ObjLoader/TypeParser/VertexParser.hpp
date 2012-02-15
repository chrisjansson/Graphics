#ifndef VERTEX_PARSER
#define VERTEX_PARSER

#include "ITypeParser.hpp"

class VertexParser : ITypeParser
{
public:
	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &line);
};

#endif