#ifndef VERTEX_PARSER
#define VERTEX_PARSER

#include "ITypeParser.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class VertexParser : public ITypeParser
{
public:
	VertexParser(DataStore &dataStore);

	void CountKeyword(const std::string &line);
	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &line);

private:
	DataStore &_dataStore;
	int _count;
};

#endif