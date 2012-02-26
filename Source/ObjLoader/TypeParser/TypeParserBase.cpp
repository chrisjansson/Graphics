#include "TypeParserBase.hpp"

TypeParserBase::TypeParserBase() : _count(0)
{

}

void TypeParserBase::CountKeyword( const std::string &line )
{
	if(CanParseLine(line))
	{
		_count++;
	}
}
