#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

#include "ObjLoader.hpp"
#include <conio.h>

void WriteStream(std::istream &stream)
{
	while(stream.good())
	{
		std::string str;
		std::getline(stream, str);
		
		std::cout << str << std::endl;
	}
}

int GetStreamLength(std::istream &stream)
{
	stream.seekg(0, std::ios::end);
	std::streampos length = stream.tellg();
	stream.seekg(0, std::ios::beg);

	return length;
}

void CopyStream(std::istream &input, std::ostream &output)
{
	int length = GetStreamLength(input);

	char *buffer = new char[length];
	
	input.read(buffer, length);
	
	int charsRead = input.gcount();
	output.write(buffer, charsRead);
}

int main(void) 
{
	std::ifstream inputStream("buddha.obj", std::ifstream::in);
	//std::ifstream inputStream("cube.obj", std::ifstream::in);
	std::stringstream memoryStream;

	CopyStream(inputStream, memoryStream);
	inputStream.close();

	clock_t initialTime = clock();

	DataStore dataStore;
	ObjLoader loader(dataStore);
	loader.Parse(memoryStream);

	clock_t endTime = clock();

	double deltaTime = ((double)(endTime - initialTime)) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time: " << deltaTime << std::endl;

	getch();

	return 0;
}