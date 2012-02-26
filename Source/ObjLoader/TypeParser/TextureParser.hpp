#ifndef TEXTURE_PARSER_H
#define TEXTURE_PARSER_H

#include "ITypeParser.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class TextureParser : public ITypeParser
{
public:
	TextureParser(DataStore &dataStore);

	void CountKeyword(const std::string &line);
	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);

private:
	DataStore &_dataStore;
	int _count;
};

#endif