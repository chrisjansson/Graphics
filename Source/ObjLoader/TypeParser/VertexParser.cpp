#include "VertexParser.hpp"

void VertexParser::ParseLine(const std::string &line)
{

}

bool VertexParser::CanParseLine(const std::string &keyWord)
{
	return keyWord.compare("v") == 0;
}
