#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <netdb.h>
#include <error.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class EchoServer {
 public:
  bool SetupSocket();
  void Start();
  EchoServer(int port);
  ~EchoServer();
 private:
  int port_;
  int socket_;
};

bool EchoServer::SetupSocket() {
  // create a socket
  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_ == -1) {
    cerr << "Error: bad socket\n";
    return false;
  }
  int ok = 1;
  // to reuse ports
  if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok)) == -1) {
    cerr << "Error: bad setsockopt\n";
    return false;
  }
  struct sockaddr_in addr;
  socklen_t length = (socklen_t)sizeof(addr);
  memset(&addr, 0, length);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port_);
  // bind address to our socket
  if (bind(socket_, (const struct sockaddr *)&addr, length) == -1) {
    cerr << "Error: bad bind\n";
    return false;
  }
  // listen for connections
  if (listen(socket_, 10) == -1) {
    cerr << "Error: bad listen\n";
    return false;
  }

  return true;
}

void EchoServer::Start() {
  char client_name[30];
  while (true) {
    struct sockaddr_in client_addr;
    socklen_t length = (socklen_t)sizeof(client_addr);
    // accept a connection
    int connfd = accept(socket_, (struct sockaddr *)&client_addr, (unsigned int *)&length);
    uint32_t client_ip = ntohl(client_addr.sin_addr.s_addr);
    uint32_t client_port = ntohs(client_addr.sin_port);
    sprintf(client_name, "%d.%d.%d.%d:%d",
            client_ip >> 24,
            (client_ip & 0x00ff0000) >> 16,
            (client_ip & 0x0000ff00) >> 8,
            (client_ip & 0x000000ff),
            client_port);
    printf("%s connected!\n", client_name);
    if (connfd == -1) {
      cerr << "Error: bad accept\n";
      return;
    }
    char buffer[1000];

    while (true) {
      // recv data from the connection
      ssize_t num_recvd = recv(connfd, buffer, 1000, MSG_NOSIGNAL);
      if (num_recvd == 0) {
        break;
      } else if (num_recvd == -1) {
        perror("bad recv");
        break;
      }
      cout << "[MSG_SIZE=" << num_recvd <<"BYTES]" << buffer << endl;
    }
    printf("%s disconnected!\n", client_name);
    close(connfd);
  }
}

EchoServer::EchoServer(int port) : socket_(-1), port_(port) { }

EchoServer::~EchoServer() {
  if (socket_ != -1) {
    close(socket_);
  }
}

int main(int argc, char *argv[]) {
  EchoServer echo_server(atoi(argv[1]));
  if (!echo_server.SetupSocket()) {
    return -1;
  }
  echo_server.Start();
  return 0;
}
