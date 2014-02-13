OUTFILE = httnp
OBJECTS = Main.o HttpServer.o HttpConnection.o

CXX = g++
CPPFLAGS = -Wall -O2 -std=c++0x -pthread
LDFLAGS =

$(OUTFILE): $(OBJECTS)
	$(CXX) -o $(OUTFILE) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS)

Main.o: HttpServer.h
HttpServer.o: HttpServer.h HttpConnection.h
HttpConnection.o: HttpServer.h HttpConnection.h

.PHONY: clean install
clean:
	test -z "$(OUTFILE)" || rm -f $(OUTFILE)
	rm -f *.o

install:
	install $(OUTFILE) /usr/local/bin
