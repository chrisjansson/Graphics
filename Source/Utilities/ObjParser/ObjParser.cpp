#include "ObjParser.hpp"
#include <vector>
#include <exception>
#include "..\VerticesFromDataGenerator.h"
#include <stdlib.h>

ObjParser::ObjParser() : _vCount(0), _vtCount(0), _vnCount(0), _fCount(0),
	_vertexIndex(0), _textureIndex(0), _faceIndex(0), _normalIndex(0)
{
}

void ObjParser::Parse(const char * filePath)
{
	FILE * inFile;
	fopen_s(&inFile, filePath, "r");

	while(!feof(inFile)) 
	{
		char buffer[LINE_LENGTH];
		fgets(buffer, LINE_LENGTH, inFile);
		std::string line(buffer);

		CountData(line);
	}
	rewind(inFile);


	AllocateBuffers();

	//_fCount = 0;

	while(!feof(inFile)) 
	{
		char buffer[LINE_LENGTH];
		fgets(buffer, LINE_LENGTH, inFile);
		std::string line(buffer);

		ParseLine(line);
	}

	fclose(inFile);

	std::cout << "Vertices: " << _vCount << std::endl;
	std::cout << "Texture coordinates: " << _vtCount << std::endl;
	std::cout << "Vertex normals: " << _vnCount << std::endl;
	std::cout << "Faces: " << _fCount << std::endl;
}

void ObjParser::ParseLine( const std::string &line )
{
	if(line.empty()) 
	{
		return;
	}

	std::stringstream lineStream;
	lineStream.str(line);

	std::string keyword;
	lineStream >> keyword;

	if(IsCommentKeyword(keyword)) 
	{
		//Comment
	}
	else if(IsVertexKeyword(keyword)) 
	{
		//Vertex
		float x, y, z;
		lineStream >> x >> y >> z;

		glm::vec3 vec(x, y, z);
		_vertices[_vertexIndex++] = vec;
	}
	else if(IsTextureKeyword(keyword)) 
	{
		//TextureCoordinate
		float x, y;
		lineStream >> x >> y;

		glm::vec2 vec(x, y);
		_textures[_textureIndex++] = vec;
	}
	else if(IsNormalKeyword(keyword)) 
	{
		//VertexNormal
		float x, y, z;
		lineStream >> x >> y >> z;

		glm::vec3 vec(x, y, z);
		_normals[_normalIndex++] = vec;
	}
	else if(IsFaceKeyword(keyword)) 
	{
		ParseFace(lineStream);

	}

	//Unrecognized keyword
}


void ObjParser::CountData(const std::string &line)
{
	if(line.empty()) 
	{
		return;
	}

	std::stringstream lineStream;
	lineStream.str(line);

	std::string keyword;
	lineStream >> keyword;
	
	if(IsCommentKeyword(keyword)) 
	{
		//Comment
	}
	else if(IsVertexKeyword(keyword)) 
	{
		//Vertex
		_vCount++;
	}
	else if(IsTextureKeyword(keyword)) 
	{
		//TextureCoordinate
		_vtCount++;
	}
	else if(IsNormalKeyword(keyword)) 
	{
		//VertexNormal
		_vnCount++;
	}
	else if(IsFaceKeyword(keyword)) 
	{
		//Face
		_fCount++;
	}

	//Unrecognized keyword
}

bool ObjParser::IsCommentKeyword( const std::string &line )
{
	return line.compare("#") == 0;
}

bool ObjParser::IsVertexKeyword( const std::string &line )
{
	return line.compare("v") == 0;
}

bool ObjParser::IsTextureKeyword( const std::string &line )
{
	return line.compare("vt") == 0;
}

bool ObjParser::IsNormalKeyword( const std::string &line )
{
	return line.compare("vn") == 0;
}

bool ObjParser::IsFaceKeyword( const std::string &line )
{
	return line.compare("f") == 0;
}

void ObjParser::AllocateBuffers()
{
	_vertices = new glm::detail::tvec3<float>[_vCount];
	_normals = new glm::detail::tvec3<float>[_vnCount];
	_textures = new glm::detail::tvec2<float>[_vtCount];

	//TODO: allocate space for face container
}

void ObjParser::ParseFace( std::stringstream &lineStream )
{
	//std::vector<std::string> faceFields;

	//std::string faceField;
	//lineStream >> faceField;
	//while(faceField.length() > 0 && !lineStream.eof()) 
	//{
	//	faceFields.push_back(faceField);
	//	lineStream >> faceField;
	//}

	//for (int i = 0; i < faceFields.size(); i++)
	//{
	//	int vertexNumber = atoi(faceFields[i].c_str());

	//	VertexPositionNormal vertex;
	//	vertex.Position = _vertices[vertexNumber - 1];
	//	vertex.Normal = _vertices[vertexNumber - 1];

	//	//_faces[_faceIndex++] = vertex;
	//}

	////Triangle
	//if(faceFields.size() == 3) 
	//{
	//	_fCount++;			
	//}
}

ObjParser::~ObjParser()
{
	delete[] _vertices;
	delete[] _normals;
	delete[] _textures;
}
