#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

namespace HttpServer {

class HttpHeader {
  public:
	HttpHeader(string);
	HttpHeader(string,string);
	~HttpHeader() {}

	string getInternalName() { return internalHeaderName; }
	string getName        () { return headerName;         }
	string getContent     () { return headerContent;      }

  private:
	string internalHeaderName;

	string headerName;
	string headerContent;
};

} // namespace

#endif
