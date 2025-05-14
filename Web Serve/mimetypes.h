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

	std::map<std::string, std::string> MimeTypeCache;
private:
	MimeTypes() {}
};

#endif // !MIMETYPES_H