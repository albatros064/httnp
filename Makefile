OUTFILE = httnp
OBJECTS = Main.o HttpServer.o HttpConnection.o HttpRequest.o HttpResponse.o HttpHeader.o

CXX = g++
CPPFLAGS = -Wall -O2 -std=c++0x -pthread
LDFLAGS =

$(OUTFILE): $(OBJECTS)
	$(CXX) -o $(OUTFILE) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS)

Main.o: HttpServer.h
HttpServer.o: HttpServer.h HttpConnection.h
HttpConnection.o: HttpServer.h HttpConnection.h HttpHeader.h
HttpRequest.o: HttpConnection.h HttpRequest.h HttpHeader.h
HttpResponse.o: HttpConnection.h HttpResponse.h HttpHeader.h

.PHONY: clean install
clean:
	test -z "$(OUTFILE)" || rm -f $(OUTFILE)
	rm -f *.o

install:
	install $(OUTFILE) /usr/local/bin
