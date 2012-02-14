#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <GLM/glm.hpp>
#include "../VerticesFromDataGenerator.h"

#define LINE_LENGTH 1024

class ObjParser
{
public:
	ObjParser();
	~ObjParser();
	void Parse(char const * filePath);
private:
	int _vCount;
	int _vtCount;
	int _vnCount;
	int _fCount;

	int _vertexIndex;
	int _textureIndex;
	int _normalIndex;
	int _faceIndex;

	glm::detail::tvec3<float> * _vertices;
	glm::detail::tvec3<float> * _normals;
	glm::detail::tvec2<float> * _textures;

	void CountData(const std::string &line);
	void AllocateBuffers();
	void ParseLine(const std::string &line);

	void ParseFace( std::stringstream &lineStream );

	bool IsCommentKeyword(const std::string &line);
	bool IsVertexKeyword(const std::string &line);
	bool IsTextureKeyword(const std::string &line);
	bool IsNormalKeyword(const std::string &line);
	bool IsFaceKeyword(const std::string &line);
};

#endif