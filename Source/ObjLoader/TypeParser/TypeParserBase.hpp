#ifndef TYPE_PARSER_BASE_H
#define  TYPE_PARSER_BASE_H

#include "ITypeParser.hpp"

class TypeParserBase : public ITypeParser
{
public:
	TypeParserBase();
	void CountKeyword(const std::string &line);
protected:
	int _count;
};

#endif