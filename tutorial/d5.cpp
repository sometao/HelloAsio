#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include "asio.hpp"



using asio::ip::udp;

std::string make_daytime_string() {
  using namespace std;  // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


int main(int argc, char* argv[]) {
  try {
    asio::io_context ioContext;
    udp::socket socket(ioContext, udp::endpoint(udp::v4(), 13));

    char recvBuf[1024];
    for(;;) {
      std::memset(recvBuf, 0, 1024);
      udp::endpoint remote;
      socket.receive_from(asio::buffer(recvBuf), remote);
      auto msg = make_daytime_string();
      asio::error_code ignoreError;
      socket.send_to(asio::buffer(msg), remote, 0, ignoreError);
    }
  } catch( std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}