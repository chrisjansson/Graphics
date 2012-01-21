#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>

#define LINE_LENGTH 1024

class ObjParser
{
public:
	ObjParser();
	void Parse(char const * filePath);

private:
	int _vCount;
	int _vtCount;
	int _vnCount;
	int _fCount;

	int _vertexInsertIndex;
	int _vertexTextureCoordinateInsertIndex;
	int _vertexNormalInsertIndex;
	int _faceInsertIndex;

	float * _vertices;
	float * _vertexCoordinates;
	float * _vertexNormals;

	void CountData(const std::string &line);
	void AllocateBuffers();
	void ParseLine(const std::string &line);
	bool IsCommentKeyword(const std::string &line);
	bool IsVertexKeyword(const std::string &line);
	bool IsVertexTextureCoordinateKeyword(const std::string &line);
	bool IsVertexNormalKeyword(const std::string &line);
	bool IsFaceKeyword(const std::string &line);
};

#endif