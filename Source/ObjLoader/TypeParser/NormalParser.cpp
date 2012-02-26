#include "NormalParser.hpp"

void NormalParser::CountKeyword(const std::string &line)
{
	if(CanParseLine(line))
	{
		_count++;
	}
}

void NormalParser::ParseLine(const std::string &line)
{
	std::stringstream lineStream;
	lineStream.str(line);

	float x, y, z;
	lineStream >> x >> y >> z;

	Normal n(x, y, z);
	_dataStore.AddNormal(n);
}

bool NormalParser::CanParseLine(const std::string &keyWord)
{
	return keyWord.compare("vn") == 0;
}

NormalParser::NormalParser(DataStore &dataStore) : _dataStore(dataStore), _count(0)
{

}