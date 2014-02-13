#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>

namespace HttpServer {

using std::string;

class HttpConnection;

void httpConnectionThread(HttpConnection*);

class HttpServer {
  public:
	HttpServer();
	~HttpServer() {}

	void run(int);

  private:
	int listeningPort;
	int listeningSocket;

	bool reconfigure;
	bool running;

	void initialize();
	void abort(string);

  protected:
};

} // namespace

#endif
