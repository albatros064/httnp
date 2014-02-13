#include "HttpRequest.h"
#include "HttpConnection.h"
#include "HttpHeader.h"

namespace HttpServer {

HttpRequest::HttpRequest(HttpConnection *conn):
  connection(conn) {
}

bool HttpRequest::hasHeader(string header) {
	return headers.count(header) > 0;
}
string HttpRequest::getHeader(string header) {
	if (hasHeader(header)) {
		return headers[header]->getContent();
	}
	return "";
}

void HttpRequest::parse() {
	int readResult;
	HttpHeader *newHeader;
	string line;
	char *buffer;

	readResult = readLine(&line);
	if (readResult == -1) {
		throw 400;
	}

	parseRequestLine(line);

	// Read header lines
	while((readResult = connection->readLine(&line)) == 0) {
		if (headerLine.length() == 0) {
			break;
		}
		newHeader = new HttpHeader(requestHeaderLine);
		// TODO: check for duplicate headers in request
		headers[newHeader->getInternalName()] = newHeader;
	}
	if (readResult == -1) {
		throw 400;
	}

	if (headers.count("content-length") > 0) {
		int contentLength = 0;
		stringstream stream;
		stream << requestHeaders["content-length"]->getContent();
		stream >> contentLength;

		if (contentLength > 0 && connection->readString(&body, contentLength) != 0) {
			throw 400;
		}
	}
}

void HttpRequest::parseRequestLine(string request) {
	int begin, end = -1, length;

	string **requestParts = { &method, &resource, &protocol };
	for (int i = 0; i < 3; i++) {
		begin = end + 1;
		end = request.find(' ', begin);

		*(requestParts[i]) = request.substr(begin, end == string::npos ? end : end - begin);
		if (end == string::npos) {
			break;
		}
	}
	
}

} // namespace
