#include "httprequest.h"

HTTPRequestMethods HTTPTextParser::GetRequestType(std::string& headers) noexcept {
	//return the request method based on the enum
	HTTPHeaderMap header_map = ParseRequest(headers);
	std::string request_type = header_map["request_type"];
	if (request_type == "GET ") return GET;
	else if (request_type == "POST ") return POST;
	else if (request_type == "PUT ") return PUT;
	else if (request_type == "DEL ") return DEL;
	else if (request_type == "HEAD ") return HEAD;
	else if (request_type == "OPTIONS ") return OPTIONS;
	else if (request_type == "TRACE ") return TRACE;
	else if (request_type == "CONNECT ") return CONNECT;
	else return GET;
}

std::string HTTPTextParser::GetRequestPath(std::string& headers) noexcept {
	HTTPHeaderMap header_map = ParseRequest(headers);
	return header_map["path"];
}

std::string HTTPTextParser::GetRequestVersion(std::string& headers) noexcept {
	HTTPHeaderMap header_map = ParseRequest(headers);
	return header_map["version"];
}

std::string HTTPTextParser::GetRequestBody(std::string& headers) noexcept {
	std::string header = "", body = "";

	size_t pos = headers.find(DBCRLF);
	if (pos != std::string::npos) {
		header = headers.substr(0, pos);
		body = headers.substr(pos + 4);  //Skip \r\n\r\n
	}
	return body;
}

/**
* Parses the HTTP request headers and returns a map of header fields.
* The first line of the request is parsed to extract the request type, path, and version.
* The function will split the request into headers and body, and parse the headers into a map.
* map is guaranteed to have the keys "request_type", "path", and "version".
* 
* returns a map containing the request type, path, version, and other headers.
* * @note The request is expected to be in the format:
* * "GET /path/to/resource HTTP/1.1\r\nHeader1: Value1\r\nHeader2: Value2\r\n\r\n"
* * @param request The raw HTTP request string.
* * @return A map containing the parsed HTTP headers. 
*/
HTTPHeaderMap HTTPTextParser::ParseRequest(std::string& request) noexcept {
    HTTPHeaderMap header_map;

    std::string header, body;

    // Separate header and body
    size_t pos = request.find(DBCRLF);
    if (pos != std::string::npos) {
        header = request.substr(0, pos);
        body = request.substr(pos + 4);  //skip "\r\n\r\n"
    }

    // Get the first line (request line)
    size_t line_end = header.find(CRLF);
    std::string request_line = header.substr(0, line_end);
    header.erase(0, line_end + 2); // Remove request line + CRLF

    // Split request line into method, path, version
    std::istringstream req_stream(request_line);
    std::string method, path, version;
    req_stream >> method >> path >> version;

    header_map["method"] = method;
    header_map["path"] = path;
    header_map["version"] = version;

    // Parse remaining headers
    while (!header.empty()) {
        size_t sep_pos = header.find(':');
        if (sep_pos == std::string::npos) break;

        std::string key = header.substr(0, sep_pos);
        header.erase(0, sep_pos + 1);

        // Trim leading spaces from value
        header.erase(0, header.find_first_not_of(' '));

        size_t line_end = header.find(CRLF);
        std::string value = header.substr(0, line_end);
        header.erase(0, line_end + 2);

        header_map[key] = value;
    }

    return header_map;
}


HTTPTextParser::HTTPTextParser() {
}

HTTPTextParser::~HTTPTextParser() {
}