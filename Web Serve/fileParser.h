#pragma once
#include <fstream>

class FileParser
{
public:
	FileParser();
	~FileParser();

	bool checkFileCorrectness (const char *filename){
		//
	}

private:

};

FileParser::FileParser()
{
	std::fopen("", "w");
}

FileParser::~FileParser()
{
}