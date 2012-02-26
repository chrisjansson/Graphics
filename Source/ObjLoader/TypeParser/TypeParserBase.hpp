#ifndef TYPE_PARSER_BASE_H
#define  TYPE_PARSER_BASE_H

#include "../DataStore/DataStore.hpp"
#include "ITypeParser.hpp"

class TypeParserBase : public ITypeParser
{
public:
	TypeParserBase(DataStore &dataStore);
	void CountKeyword(const std::string &line);
protected:
	int _count;
	DataStore &_dataStore;
};

#endif