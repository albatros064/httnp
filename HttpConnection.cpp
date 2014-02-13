#include <string>
#include <iostream>
#include <sstream>

#include <assert.h>
#include <unistd.h>

#include "HttpConnection.h"
#include "HttpHeader.h"
#include "HttpServer.h"

namespace HttpServer {

using std::string;
using std::cout;
using std::stringstream;

HttpConnection::HttpConnection(ConferenceHttpServer *httpServer, ConferenceManager *conferenceManager, int socket):
  server(httpServer), clientSocket(socket) {
}
HttpConnection::~HttpConnection() {
	if (clientSocket >= 0) {
		close(clientSocket);
	}
}
void HttpConnection::handleRequest() {
	while (true) {
		try {
			request = new HttpRequest(this);
			request.parse();

			response = new HttpResponse;

			// Handle application hooks
			// handleHook(request->getMethod(), request, response);
		}
		catch (int exception) {
			// Handle error
			if (response) {
				delete response;
			}

			response = new HttpResponse;
			response->setCode(exception);
			response->setCodeText("Nope");
			response->setBody("Oh, you in trouble now...");
		}

		writeString(response->render());

		delete response;

		// TODO: persistent connections
		break;
	}
}

int HttpConnection::readLine(sting *outLine, char *buffer, int max) {
	if (!buffer) {
		buffer = malloc(HTTP_REQUEST_LINE_SIZE);
		max = HTTP_REQUEST_LINE_SIZE;
		if (!buffer) {
			throw 500;
		}
	}

	outLine->clear();
	do {
		readResult = readLine(buffer, max);
		outLine->append(buffer);
	}
	while (readResult == -2);

	return readResult;
}

int HttpConnection::readLine(char *buffer, int max) {
	int totalRead = 0;
	int returnValue = -2;
	char c;
	while (totalRead < max - 1) {
		if (read(clientSocket, &c, 1) == 0) {
			returnValue = -1;
			break;
		}
		if (totalRead > 0 && buffer[totalRead - 1] == '\r' && c == '\n') {
			returnValue = 0;
			totalRead--;
			break;
		}
		buffer[totalRead++] = c;
	}
	buffer[totalRead] = '\0';
	return returnValue;
}

int HttpConnection::readString(string *outString, int count) {
	outString->clear();
	char *buffer = malloc(count);
	if (!buffer) {
		throw 500;
	}

	int result = readString(buffer, count);
	outString->append(buffer, result);
	if (result < count) {
		return -1;
	}
	return 0;
}
int HttpConnection::readString(char *buffer, int count) {
	return read(clientSocket, buffer, count);
}

int HttpConnection::writeString(string outString) {
	return write(clientSocket, outString.c_str(), outString.length());
}

} // namespace
