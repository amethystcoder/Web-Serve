#include "fileParser.h"


FileParser::FileParser(const char* filename)
{
	fileRead.open("", std::ios::binary | std::ios::ate);
	if (fileRead.fail()) return;

	std::streamsize size = fileRead.tellg();
	if (size == -1) return;
	fileRead.seekg(0, std::ios::beg);

	std::string content(size, 0);
	fileRead.read(&content[0], size);
	//this should be considered unneccessary
	fileContent = content;
}

FileParser::~FileParser()
{
	fileRead.close();
}

bool FileParser::check_is_html(const std::string& filename) {
	//check if the file is a valid html file
	//valid files have the .html extension
	std::string file = filename;
	if (file.find(".html") == std::string::npos) return false;
	return true;
}

std::map<std::string, std::string> FileParser::parseAttributes(const std::string& input) {
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

void FileParser::parseStringTemplateLiteral(const std::string& input) {
	//parse the string template literal
	//this is a simple implementation that does not handle all cases
	//it is just a placeholder for now
	//instead of using a string, use a map
	//this is just a note to myself
	std::vector<std::vector<std::string>> result;
	std::regex pattern(R"(\{([^{}]+)\})");
	std::smatch match;
	std::string str = input;

	while (std::regex_search(str, match, pattern)) {
		std::string content = match[1];
		//get the string between the curly braces
		content.replace(content.find("{"), 1, "");
		content.replace(content.find("}"), 1, "");
	}
}

std::vector<std::string> FileParser::splitString(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}


TagDataList FileParser::parse_html_content(std::string& html_text)
{
	html_text.erase(std::remove(html_text.begin(), html_text.end(), '\r'), html_text.end());
	html_text.erase(std::remove(html_text.begin(), html_text.end(), '\n'), html_text.end());

	//master tags are the tags that are not nested or are the root tags in a string
	//for example in the html text <server><api></api></server> server is a master tag
	//child tags are not accessed
	TagDataList master_tags;
	//regex to parse html text
	std::regex html_regex(R"(<([^<>/\s]+)((?:\s+[^<>/\s=]+=(?:"[^"]*"|'[^']*'|[^'"\s<>]*))*)>(.*?)<\/\1>|<([^<>/\s]+)((?:\s+[^<>/\s=]+=(?:"[^"]*"|'[^']*'|[^'"\s<>]*))*)\/>)");
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

std::string FileParser::readHtmlFile(const std::string& html_file){
	if (!check_is_html(html_file)) return "";
	std::ifstream file(html_file);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

//html file like index.html
TagDataList FileParser::parse_html_file(const std::string& html_file)
{
	std::string html_text = readHtmlFile(html_file);
	if (html_text == "") return TagDataList();
	return parse_html_content(html_text);
}

TagDataList FileParser::determineParseType(std::string& input) {
	//check if the input is a file or a string
	//if the input is a file then return the parsed file content
	//if the input is a string then return the parsed string content
	//if the input is neither a file nor a string then return an empty string
	return input.ends_with(".html") ? parse_html_file(input) : parse_html_content(input);
}