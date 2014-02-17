#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

#include "HttpConnection.h"
#include "HttpHeader.h"
#include "HttpRequest.h"

namespace HttpServer {

using std::cout;

using std::vector;
using std::istringstream;
using std::istream_iterator;

HttpRequest::HttpRequest():
  connection(0) {
}

void HttpRequest::parse(HttpConnection *conn) {
	connection = conn;
	int readResult;
	HttpHeader *newHeader;
	string line;

	readResult = connection->readLine(&line);
	if (readResult == -1) {
		throw 400;
	}

	parseRequestLine(line);

	// Read header lines
	while((readResult = connection->readLine(&line)) == 0) {
		if (line.length() == 0) {
			break;
		}
		newHeader = new HttpHeader(line);
		// TODO: check for duplicate headers in request
		headers[newHeader->getInternalName()] = newHeader;
	}
	if (readResult == -1) {
		throw 400;
	}

	if (headers.count("content-length") > 0) {
		int contentLength = 0;
		stringstream stream;
		stream << headers["content-length"]->getContent();
		stream >> contentLength;
		cout << "Content-Length: " << contentLength << "\n";

		if (contentLength > 0 && connection->readString(&body, contentLength) != 0) {
			throw 400;
		}
	}
}

void HttpRequest::parseRequestLine(string request) {
	istringstream requestStream(request);

	vector<string> vec { istream_iterator<string>(requestStream), istream_iterator<string>() };

	if (vec.size() > 0) {
		method = vec[0];
	}
	if (vec.size() > 1) {
		resource = vec[1];
	}
	if (vec.size() > 2) {
		protocol = vec[2];
	}

	cout << "Method: " << method << "\nResource: " << resource << "\nProtocol: " << protocol << "\n";
}

} // namespace
