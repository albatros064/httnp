#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <map>

namespace HttpServer {

using std::map;
using std::string;

class HttpHeader;

class HttpResponse {
  public:
	HttpResponse();
	~HttpResponse();

	void setCode    (int    code ) { this->code     = code;  }
	void setCodeText(string text ) { this->codeText = text;  }
	void setProtocol(string proto) { this->protocol = proto; }
	void setBody    (string body ) { this->body     = body;  }

	void setHeader(string,string);
	void removeHeader(string);

	string render();
  private:
	int    code;
	string codeText;
	string protocol;
	string body;

  	map<string,HttpHeader*> headers;
};

} // namespace

#endif
