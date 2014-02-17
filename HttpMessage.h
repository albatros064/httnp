#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include <map>
#include <string>

namespace HttpServer {

using std::string;
using std::map;

class HttpHeader;

class HttpMessage {
  public:
	HttpMessage();
	~HttpMessage();

	void   setHeader   (string,string);
	void   removeHeader(string);
	bool   hasHeader   (string);
	string getHeader   (string);

	string render();

	string getProtocol() { return protocol; }
	string getBody    () { return body;     }
	void setProtocol(string proto) { this->protocol = proto; }
	void setBody    (string body ) { this->body     = body;  }

  private:
  protected:
	string protocol;
	string body;

	map<string,HttpHeader*> headers;

	virtual string renderFirstLine() = 0;

	static string EOL;
};

} // namespace

#endif
