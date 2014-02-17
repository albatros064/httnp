#include <sstream>

#include "HttpResponse.h"
#include "HttpHeader.h"

namespace HttpServer {

using std::stringstream;

HttpResponse::HttpResponse() {
	protocol = "HTTP/1.1";
	code = 200;
	codeText = "OK";
}

string HttpResponse::renderFirstLine() {
	stringstream outStream;
	outStream << protocol << " " << code << " " << codeText;
	return outStream.str();
}

} // namespace
