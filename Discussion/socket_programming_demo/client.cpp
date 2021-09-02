
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <netdb.h>

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class EchoClient {
 public:
  bool SetupSocket();
  void SendMsg();
  EchoClient(const string &hostname, int port);
  ~EchoClient();

 private:
  string hostname_;
  int port_;
  int socket_;
};

bool EchoClient::SetupSocket() {
  // create a socket
  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_ == -1) {
    cerr << "Error: bad socket\n";
    return false;
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  // resolve the address of the server
  struct hostent *host = gethostbyname(hostname_.c_str());
  if (host == nullptr) {
    cerr << "Error: bad hostname\n";
    return false;
  }
  memcpy(&(addr.sin_addr), host->h_addr, host->h_length);
  addr.sin_port = htons(port_);
  // connect to the server
  if (connect(socket_, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    cerr << "Error: bad connect\n";
    return false;
  }
  return true;
}

void EchoClient::SendMsg() {
  string msg;
  while (true) {
    cout << "Please input your msg: ";
    getline(cin, msg);
    if (msg == "exit") {
      break;
    }
    // send data to the server
    auto num_sent = send(socket_, msg.c_str(), msg.size() + 1, MSG_NOSIGNAL);
    cout << "num_sent: " << num_sent << endl;
    if (num_sent == -1) {
      perror("bad send");
      break;
    }
  }
  close(socket_);
}

EchoClient::EchoClient(const string &hostname, int port) :
    hostname_(hostname), port_(port), socket_(-1) { }

EchoClient::~EchoClient() {
  if (socket_ != -1) {
    close(socket_);
  }
}

int main (int argc, char *argv[]) {
  EchoClient echo_client(argv[1], atoi(argv[2]));
  if (!echo_client.SetupSocket()) {
    return -1;
  }
  echo_client.SendMsg();
  return 0;
}
