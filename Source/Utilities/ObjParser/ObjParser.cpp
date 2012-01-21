#include "ObjParser.hpp"

ObjParser::ObjParser() : _vCount(0), _vtCount(0), _vnCount(0), _fCount(0),
	_vertexInsertIndex(0), _vertexTextureCoordinateInsertIndex(0), _faceInsertIndex(0), _vertexNormalInsertIndex(0)
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
		int index = _vertexInsertIndex * 3;
		float x, y, z;
		lineStream >> x >> y >> z;

		_vertices[index + 0] = x;
		_vertices[index + 1] = y;
		_vertices[index + 2] = z;

		_vertexInsertIndex++;
	}
	else if(IsVertexTextureCoordinateKeyword(keyword)) 
	{
		//TextureCoordinate
		int index = _vertexTextureCoordinateInsertIndex * 2;
		float x, y;
		lineStream >> x >> y;

		_vertices[index + 0] = x;
		_vertices[index + 1] = y;

		_vertexTextureCoordinateInsertIndex++;
	}
	else if(IsVertexNormalKeyword(keyword)) 
	{
		//VertexNormal
		int index = _vertexNormalInsertIndex * 3;
		float x, y, z;
		lineStream >> x >> y >> z;

		_vertices[index + 0] = x;
		_vertices[index + 1] = y;
		_vertices[index + 2] = z;

		_vertexNormalInsertIndex++;
	}
	else if(IsFaceKeyword(keyword)) 
	{
		//Face
		//_fCount++;
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
	else if(IsVertexTextureCoordinateKeyword(keyword)) 
	{
		//TextureCoordinate
		_vtCount++;
	}
	else if(IsVertexNormalKeyword(keyword)) 
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

bool ObjParser::IsVertexTextureCoordinateKeyword( const std::string &line )
{
	return line.compare("vt") == 0;
}

bool ObjParser::IsVertexNormalKeyword( const std::string &line )
{
	return line.compare("vn") == 0;
}

bool ObjParser::IsFaceKeyword( const std::string &line )
{
	return line.compare("f") == 0;
}

void ObjParser::AllocateBuffers()
{
	_vertices = new float[_vCount * 3];
	_vertexCoordinates = new float[_vCount * 2];
	_vertexNormals = new float[_vCount * 3];

	//TODO: allocate space for face container
}
