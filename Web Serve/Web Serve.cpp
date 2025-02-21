#include "socket.hpp"
#include <system_error>
#include <iostream>
#include "cleansocket.h"
#include "clientsock.h"
#include "serversock.h"
#include "ast.h"
#include <regex>


int main() {
	std::string html_text = "<server port='5000'><api><routes></routes></api><DB class='weird class'/></server><content></content> <DB class='weird class'/>";

	
	parse_html(html_text);
	//create a tree of the html text



}

void parse_html(std::string html_text)
{
	//regex to parse html text
	std::regex html_regex(R"(<([^<>/\s]+)([^<>]*)>(.*?)<\/\1>|<([^<>/\s]+)([^<>]*)\/>)");
	std::smatch match;

	std::string temp = html_text;


	//parse the html text
	//std::string::const_iterator searchStart(html_text.cbegin());
	while (std::regex_search(temp, match, html_regex))
	{
		if (match[1].matched) {
			// Opening and closing tag like <html> </html>
			std::string tag = match[1];
			std::string attributes = match[2];
			std::string content = match[3];
		}
		else {
			// Self closing tag like <br/>
			std::string tag = match[4];
			std::string attributes = match[5];
		}
		temp = match.suffix().str();
	}

}