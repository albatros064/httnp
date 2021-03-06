#include <algorithm>

#include "HttpHeader.h"

namespace HttpServer {

HttpHeader::HttpHeader(string source) {
	populate(source);
}

HttpHeader::HttpHeader(string name, string content):
  headerContent(content) {
  	headerName = internalizeName(name);
}

void HttpHeader::populate(string source) {
	size_t colonChar = source.find(':');
	headerName    = source.substr(0, colonChar);
	headerContent = source.substr(colonChar + 1);
	internalizeName();
}

void HttpHeader::internalizeName() {
	internalHeaderName.resize(headerName.length());
	std::transform(headerName.begin(), headerName.end(), internalHeaderName.begin(), ::tolower);
}

} // namespace
