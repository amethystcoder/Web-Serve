#ifndef MIMETYPES_H

#define MIMETYPES_H

#include <map>
#include "fileParser.h"

class MimeTypes
{
public:

	static MimeTypes getInstance() {
		static MimeTypes mimeTypeInstance;
		return mimeTypeInstance;
	}

	~MimeTypes() = default;

	std::string getMimeType(const std::string& filename);

	bool mime_type_exists(const std::string& extension_name);
	
	//common mime types that would be commonly used in a web server
	std::map<std::string, std::string> MimeTypeCache = {
	{ "html", "text/html" },
	{ "css", "text/css" },
	{ "js", "application/javascript" },
	{ "json", "application/json" },
	{ "xml", "application/xml" },
	{ "txt", "text/plain" },
	{ "png", "image/png" },
	{ "jpg", "image/jpeg" },
	{ "jpeg", "image/jpeg" },
	{ "bmp", "image/bmp" },
	{ "ico", "image/x-icon" },
	{ "webp", "image/webp" },
	{ "mp4", "video/mp4" },
	{ "mp3", "audio/mpeg" },
	{ "wav", "audio/wav" },
	{ "ogg", "audio/ogg" },
	{ "gif", "image/gif" },
	{ "svg", "image/svg+xml" },
	{ "woff", "font/woff" },
	{ "woff2", "font/woff2" }
	};

private:
	MimeTypes() {}
};

#endif // !MIMETYPES_H