#ifndef FACE_PARSER_H
#define FACE_PARSER_H

#include "TypeParserBase.hpp"

class FaceParser : public TypeParserBase
{
public:
	FaceParser(DataStore &dataStore);

	void ParseLine(const std::string &line);
	bool CanParseLine(const std::string &keyWord);
	void AllocateSpace();
};

#endif