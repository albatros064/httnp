#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <map>

namespace HttpServer {

using std::string;
using std::map;

class HttpConnection;
class HttpHeader;

class HttpRequest {
  public:
	HttpRequest(HttpConnection*);
	~HttpRequest();

	void parse();

	string getMethod  () { return method;   }
	string getResource() { return resource; }
	string getProtocol() { return protocol; }
	string getBody    () { return body;     }

	bool   hasHeader(string);
	string getHeader(string);


  private:
	string method;
	string resource;
	string protocol;
	string body;
	map<string,HttpHeader*> headers;

	HttpConnection *connection;

	void parseRequestLine(string);
};

} // namespace

#endif
