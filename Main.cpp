#include "HttpServer.h"

int main(int argc, char **argv) {
	HttpServer::HttpServer server;
	server.run(10066);

	return 0;
}
