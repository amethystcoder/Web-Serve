#include "mimetypes.h"
#include <iostream>

std::string MimeTypes::getMimeType(const std::string& extension_name)
{
	auto it = MimeTypeCache.find(extension_name);
	if (it != MimeTypeCache.end())
	{
		return it->second + "\n\n";
	}
	else
	{
		std::string JSON_string = FileParser::readFile("mimetypes.json");
		std::map<std::string,std::string> mimeType = FileParser::parseJSON(JSON_string);
		//search for the extension name in the map
		auto it = mimeType.find(extension_name);
		if (it != mimeType.end())
		{
			MimeTypeCache[extension_name] = it->second;
			return it->second + "\n\n";
		}
		else
		{
			return "text/plain\n\n";
		}
	}
}

bool MimeTypes::mime_type_exists(const std::string& extension_name)
{
	return getMimeType(extension_name) != "text/plain\n\n";
}