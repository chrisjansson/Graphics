#ifndef ITYPE_PARSER_H
#define ITYPE_PARSER_H

#include <string>

class ITypeParser 
{
public:
	virtual ~ITypeParser() {}
	virtual void ParseLine(const std::string &line) = 0;
	virtual bool CanParseLine(const std::string &keyWord) = 0;
};

#endif