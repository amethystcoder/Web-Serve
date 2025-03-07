#pragma once
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>

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

	bool checkFileCorrectness (const char *filename){
		//change later
		return true;
	}

	std::map<std::string, std::string> parseAttributes(const std::string& input) {
		std::map<std::string, std::string> result;
		std::regex pattern(R"((\w+)='([^']*)'|(\w+))");
		std::smatch match;
		std::string str = input;

		while (std::regex_search(str, match, pattern)) {
			if (match[1].matched) { // Matched key='value' pattern
				result[match[1]] = match[2];
			}
			else if (match[3].matched) { // Matched standalone key
				result[match[3]] = ""; // Assign empty value
			}
			str = match.suffix();
		}

		return result;
	}

	static TagDataList parse_html_content(const std::string& html_text)
	{
		//master tags are the tags that are not nested or are the root tags in a string
		//for example in the html text <server><api></api></server> server is a master tag
		//child tags are not accessed
		TagDataList master_tags;
		//regex to parse html text
		std::regex html_regex(R"(<([^<>/\s]+)([^<>]*)>(.*?)<\/\1>|<([^<>/\s]+)([^<>]*)\/>)");
		std::smatch match;

		std::string temp = html_text;

		//parse the html text
		//std::string::const_iterator searchStart(html_text.cbegin());
		while (std::regex_search(temp, match, html_regex))
		{
			if (match[1].matched) {
				//Opening and closing tag like <html> </html>
				std::string tag = match[1];
				std::string attributes = match[2];
				std::string content = match[3];
				HTMLTagData tag_data;
				tag_data.tag = tag;
				tag_data.attributes = attributes;
				tag_data.content = content;
				master_tags.push_back(tag_data);
			}
			else {
				//Self closing tag like <br/>
				std::string tag = match[4];
				std::string attributes = match[5];
				HTMLTagData tag_data;
				tag_data.tag = tag;
				tag_data.attributes = attributes;
				tag_data.content = "";
				master_tags.push_back(tag_data);
			}
			temp = match.suffix().str();
		}

		return master_tags;
	}


private:
	std::fstream fileRead;
	std::string fileContent;
};

FileParser::FileParser(const char* filename)
{
	fileRead.open("", std::ios::binary | std::ios::ate);
	if (fileRead.fail()) return;

	std::streamsize size = fileRead.tellg();
	if (size == -1) return;
	fileRead.seekg(0, std::ios::beg);

	std::string content(size, '/0');
	fileRead.read(&content[0], size);
	//this should be considered unneccessary
	fileContent = content;
}

FileParser::~FileParser()
{
	fileRead.close();
}
