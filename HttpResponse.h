#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <map>

namespace HttpServer {

using std::map;
using std::string;

class HttpResponse {
  public:
	HttpResponse();
	~HttpResponse();

	void setCode(int);
	void setCodeText(string);
	void setProtocol(string);
	void setHeader(string,string);
	void removeHeader(string);
	void setBody(string);

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
