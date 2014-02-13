#include <string>
#include <iostream>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "HttpServer.h"
#include "HttpConnection.h"

namespace HttpServer {

using std::string;
using std::thread;
using std::cout;
using std::endl;

HttpServer::HttpServer():
  listeningSocket(-1),
  reconfigure(true), running(true) {
}

void HttpServer::run(int port) {
	int clientSocket;
	struct sockaddr_in clientAddress;

	socklen_t clientAddressLength = sizeof(clientAddress);
	
	listeningPort = port;

	while (running) {
		if (reconfigure) {
			initialize();
		}
		clientSocket = accept(listeningSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
		if (clientSocket >= 0) {
			HttpConnection *newConnection = new HttpConnection(this, clientSocket);
			thread *newThread = new thread(httpConnectionThread, newConnection);
		}
	}
}

void HttpServer::initialize() {
	struct sockaddr_in serverAddress;

	if (listeningSocket >= 0) {
		close(listeningSocket);
		return;
	}

	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket < 0) {
		abort("EE Could not open socket.");
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port   = htons(listeningPort);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	for (int i = 0; i < 8; i++) {
		serverAddress.sin_zero[i] = 0;
	}

	if (bind(listeningSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		abort("EE Could not bind to requested port.");
	}

	listen(listeningSocket,5);

	reconfigure = false;
}

void HttpServer::abort(string message) {
	cout << message << endl;
	exit(1);
}

void httpConnectionThread(HttpConnection *connection) {
	connection->handleRequest();
	delete connection;
}

} // namespace
