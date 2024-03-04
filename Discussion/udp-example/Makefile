all: server.exe client.exe

client.exe: client.cpp
	gcc -o client.exe client.cpp

server.exe: server.cpp
	gcc -o server.exe server.cpp

clean:
	rm -rf *.exe