#ifndef TEXTURE_PARSER_H
#define TEXTURE_PARSER_H

#include "TypeParserBase.hpp"
#include "../DataStore/DataStore.hpp"

#include <sstream>

class TextureParser : public TypeParserBase
{
public:
	TextureParser(DataStore &dataStore);

	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);
	void AllocateSpace();

private:
	DataStore &_dataStore;
};

#endif