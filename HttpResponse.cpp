#include "HttpResponse.h"
#include "HttpHeader.h"

namespace HttpServer {

HttpResponse::HttpResponse() {}
HttpResponse::~HttpResponse() {
	for (
		map<string,HttpHeader*>::iterator i = headers.begin();
		i != headers.end();
		i++
	) {
		delete i->second;
	}
}

void HttpResponse::setHeader(string name, string content) {
	HttpHeader *newHeader = new HttpHeader(name, content);
	string internalName = newHeader->getInternalName();

	if (headers.count(internalName) > 0) {
		delete headers[internalName];
	}

	headers[internalName] = newHeader;
}

void HttpResponse::removeHeader(string name) {
}

string HttpResponse::render() {
	return "";
}

} // namespace
