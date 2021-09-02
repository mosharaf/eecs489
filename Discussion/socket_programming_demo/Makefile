all: echo_server.exe echo_client.exe

echo_server.exe: server.cpp
	g++ -std=c++17 -g -o echo_server.exe server.cpp

echo_client.exe: client.cpp
	g++ -std=c++17 -g -o echo_client.exe client.cpp

clean:
	rm -rf *.exe