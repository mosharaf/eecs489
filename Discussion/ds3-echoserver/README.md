# Echoserver

This implements a simple echo server that uses select() to handle multiple concurrent client connections. This code will be covered in Discussion 3, and will be a useful reference while completing Project 2. 

You can view the man page for select here: https://man7.org/linux/man-pages/man2/select.2.html. 

A client and echoserver executable are provided; the client sends a specified message to the echo server every two seconds. When the server receives a client message, it echoes the message back. 

You can build this project by using the standard CMake build process:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

You can run the echo server as follows:
```
./echoserver 
    -p [server-port] (Default: 8888)
```

You can run the client as follows:
```
./client 
    -m [message]     (Required)
    -p [server-port] (Default: 8888)
    -h [server-hostname] (Default: localhost)
```

Note that the echo server must be running before any clients can connect. 

## Exercise
To become more familiar with this codebase and working with select(), implement
a **hearbeat server** and configure the echo server to use the heartbeat server to
listen for stay-alive messages. 

On startup, the echo server should establish a connection to the heartbeat server (as a client). 
Every `n` seconds, the heartbeat server should send a "Keep-Alive" message to every connected echo server. 
If an echo server does not receive a message from the heartbeat server over any `2n` second interval, the 
echo server should exit gracefully, closing all client connections with some appropriate summary message. 

Some considerations:
- You should first start the heartbeat server, then the echo server, and then the client. 
- The heartbeat server does not need to use select() 

