#ifndef TEXTURE_PARSER_H
#define TEXTURE_PARSER_H

#include "ITypeParser.hpp"

class TextureParser : ITypeParser
{
public:
	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);
};

#endif