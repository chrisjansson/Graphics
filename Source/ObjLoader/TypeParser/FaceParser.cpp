#include "FaceParser.hpp"

void FaceParser::ParseLine( const std::string &line )
{
	//split strings and all yao
}

bool FaceParser::CanParseLine( const std::string &keyWord )
{
	return keyWord.compare("f") == 0;
}

void FaceParser::AllocateSpace()
{
	//????
}

FaceParser::FaceParser(DataStore &dataStore) : TypeParserBase(dataStore)
{

}
