#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <string>
#include <sstream>
#include <map>

#define HTTP_REQUEST_LINE_SIZE 512

namespace HttpServer {

using std::string;
using std::stringstream;
using std::map;

class HttpServer;
class HttpRequest;
class HttpResponse;

class HttpConnection {
  public:
	HttpConnection(HttpServer*,int);
	~HttpConnection();

	void handleRequest();

  private:
	HttpServer *server;

	int clientSocket;

	HttpRequest  *request;
	HttpResponse *response;

	int readLine(string*,char *b=0,int m=0);
	int readLine(char*,int);
	int readString(string*,int);
	int readString(char*,int);

	friend class HttpRequest;
};

} // namespace

#endif
