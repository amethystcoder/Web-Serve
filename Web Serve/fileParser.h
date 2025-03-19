#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <map>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <sstream>
#include <algorithm>

struct HTMLTagData {
	std::string tag;
	std::string attributes;
	std::string content;
};

typedef std::vector<HTMLTagData> TagDataList;


//utility function
class FileParser
{
public:
	FileParser(const char* filename);
	~FileParser();

	FileParser& operator = (const FileParser&) = delete;
	FileParser(const FileParser&) = delete;

	static bool check_is_html(const std::string& filename);

	static std::map<std::string, std::string> parseAttributes(const std::string& input);

	static TagDataList parse_html_content(std::string& html_text);

	//html file like index.html
	static TagDataList parse_html_file(const std::string& html_file);
	static TagDataList determineParseType(std::string& input);
	

private:
	std::fstream fileRead;
	std::string fileContent;
};


#endif // FILEPARSER_H