# Echoserver

This implements a simple echoserver that uses select() to handle multiple concurrent client connections. This code will be covered in Discussion 3, and will be a useful reference while completing Project 2. 

You can view the man page for select here: https://man7.org/linux/man-pages/man2/select.2.html. 

A client and server executable are provided; the client sends a specified message to the server every two seconds. When the server receives a client message, it echoes the message back. 

You can build this project by using the standard CMake build process:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

You can run the server as follows:
```
./server 
    -p [server-port] (Default: 8888)
```

You can run the client as follows:
```
./client 
    -m [message]     (Required)
    -p [server-port] (Default: 8888)
    -h [server-hostname] (Default: localhost)
```

Note that the server must be running before any clients can connect. 

