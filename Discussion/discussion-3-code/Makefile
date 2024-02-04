CXX = g++
CXXFLAGS = -g -std=c++11 -pedantic

all: server client

server: echo_server.cpp
	$(CXX) $(CXXFLAGS) echo_server.cpp -o echo_server

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client

clean:
	rm -rf client echo_server *.dSYM

.PHONY: clean