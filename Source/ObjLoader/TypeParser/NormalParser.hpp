#ifndef NORMAL_PARSER_H
#define NORMAL_PARSER_H

#include "ITypeParser.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class NormalParser : ITypeParser
{
public:
	NormalParser(DataStore &dataStore);

	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);
	
private:
	DataStore &_dataStore;
};

#endif