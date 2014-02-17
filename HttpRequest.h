#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <map>

#include "HttpMessage.h"

namespace HttpServer {

using std::string;
using std::map;

class HttpConnection;
class HttpHeader;

class HttpRequest : public HttpMessage {
  public:
	HttpRequest();
	~HttpRequest() {}

	void parse(HttpConnection*);

	string getMethod  () { return method;   }
	string getResource() { return resource; }

  private:
  protected:
	string method;
	string resource;

	HttpConnection *connection;

	void parseRequestLine(string);

	virtual string renderFirstLine();
};

} // namespace

#endif
