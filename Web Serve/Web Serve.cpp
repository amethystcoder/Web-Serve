#include "socket.hpp"
#include <system_error>
#include <iostream>
#include "cleansocket.h"
#include "clientsock.h"
#include "serversock.h"
#include "ast.h"
#include <regex>


int main() {
	std::string html_text = "<server><api><routes></routes></api></server>";

	//regex to parse the html text
	std::regex html_regex("<(\\w+)>");
	std::smatch match;


	//parse the html text
	std::string::const_iterator searchStart(html_text.cbegin());
	while (std::regex_search(searchStart, html_text.cend(), match, html_regex))
	{
		std::cout << "Match: " << match[1] << std::endl;
		searchStart = match.suffix().first;
	}

	//create a tree of the html text



}