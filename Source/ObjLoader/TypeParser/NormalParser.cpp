#include "NormalParser.hpp"

NormalParser n;

void NormalParser::ParseLine(const std::string &line)
{

}

bool NormalParser::CanParseLine(const std::string &keyWord)
{
	return keyWord.compare("vn") == 0;
}
