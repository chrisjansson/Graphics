#ifndef TEXTURE_PARSER_H
#define TEXTURE_PARSER_H

#include "ITypeParser.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class TextureParser : ITypeParser
{
public:
	TextureParser(DataStore &dataStore);

	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);

private:
	DataStore &_dataStore;
};

#endif