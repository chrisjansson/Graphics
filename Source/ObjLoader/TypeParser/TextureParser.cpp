#include "TextureParser.hpp"

void TextureParser::ParseLine(const std::string &line)
{
	std::stringstream lineStream;
	lineStream.str(line);

	float x, y;
	lineStream >> x >> y;

	Texture t(x, y);
	_dataStore.AddTexture(t);
}

bool TextureParser::CanParseLine(const std::string &keyWord)
{
	return keyWord.compare("v") == 0;
}

TextureParser::TextureParser(DataStore &dataStore) : _dataStore(dataStore)
{

}
