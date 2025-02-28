#pragma once
#include <fstream>
#include <vector>
#include "ast.h"
#include <regex>


class FileParser
{
public:
	FileParser();
	~FileParser();

	bool checkFileCorrectness (const char *filename){
		//change later
		return true;
	}

	static TagDataList parse_html_content(std::string html_text)
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

};

FileParser::FileParser()
{
	std::fstream fileRead("");
	while (true)
	{

	}
}

FileParser::~FileParser()
{
}