#include <sstream>
#include "HttpMessage.h"
#include "HttpHeader.h"

namespace HttpServer {

using std::stringstream;

string HttpMessage::EOL = "\r\n";

HttpMessage::HttpMessage() {
}

HttpMessage::~HttpMessage() {
	for (
		map<string,HttpHeader*>::iterator i = headers.begin();
		i != headers.end();
		i++
	) {
		delete i->second;
	}
}

void HttpMessage::setHeader(string name, string content) {
	HttpHeader *newHeader = new HttpHeader(name, content);
	string internalName = newHeader->getInternalName();

	if (headers.count(internalName) > 0) {
		delete headers[internalName];
	}

	headers[internalName] = newHeader;
}

void HttpMessage::removeHeader(string name) {
}
bool HttpMessage::hasHeader(string name) {
	return headers.count(name) > 0;
}
string HttpMessage::getHeader(string name) {
	if (hasHeader(name)) {
		return headers[name]->getContent();
	}
	return "";
}

string HttpMessage::render() {
	stringstream outStream;

	outStream << renderFirstLine() << EOL;

	setHeader(string("Content-Length"), string("" + body.length));

	for (
		map<string,HttpHeader*>::iterator i = headers.begin();
		i != headers.end();
		i++
	) {
		outStream << i->second->render() << EOL;
	}

	outStream << EOL;

	if (body.length() > 0) {
		outStream << body;
	}

	return outStream.str();
}

} // namespace
