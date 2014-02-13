#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>

namespace HttpServer {

using std::string;

class HttpHeader {
  public:
  	HttpHeader() {}
	HttpHeader(string);
	HttpHeader(string,string);
	~HttpHeader() {}

	void populate(string);

	string getInternalName() { return internalHeaderName; }
	string getName        () { return headerName;         }
	string getContent     () { return headerContent;      }

  private:
	string internalHeaderName;

	string headerName;
	string headerContent;

	void internalizeName();
};

} // namespace

#endif
