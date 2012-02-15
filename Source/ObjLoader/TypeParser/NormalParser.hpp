#ifndef NORMAL_PARSER_H
#define NORMAL_PARSER_H

#include "ITypeParser.hpp"

class NormalParser : ITypeParser
{
public:
	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);
};

#endif