#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <map>

#include "HttpMessage.h"

namespace HttpServer {

using std::map;
using std::string;

class HttpHeader;

class HttpResponse : public HttpMessage {
  public:
	HttpResponse();
	~HttpResponse();

	void setCode    (int    code ) { this->code     = code;  }
	void setCodeText(string text ) { this->codeText = text;  }

  protected:
	int    code;
	string codeText;

	virtual string renderFirstLine();
};

} // namespace

#endif
