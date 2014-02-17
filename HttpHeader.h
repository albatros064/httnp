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

	string getName        () { return headerName;         }
	string getContent     () { return headerContent;      }

	static string internalizeName(string);

  private:
	string headerName;
	string headerContent;

};

} // namespace

#endif
