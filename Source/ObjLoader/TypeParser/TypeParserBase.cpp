#include "TypeParserBase.hpp"

TypeParserBase::TypeParserBase(DataStore &dataStore) : _count(0), _dataStore(dataStore)
{

}

void TypeParserBase::CountKeyword( const std::string &line )
{
	if(CanParseLine(line))
	{
		_count++;
	}
}
