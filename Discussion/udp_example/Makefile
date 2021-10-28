all: server.exe client.exe

client.exe: client.c
	gcc -o client.exe client.c

server.exe: server.c
	gcc -o server.exe server.c

clean:
	rm -rf *.exe