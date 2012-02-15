#include "TextureParser.hpp"

TextureParser t;

void TextureParser::ParseLine( const std::string &line )
{

}

bool TextureParser::CanParseLine( const std::string &keyWord )
{
	return keyWord.compare("v") == 0;
}