#include <iostream>
#include "asio.hpp"



using asio::ip::udp;

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    asio::io_context ioContext;

    udp::resolver resolver(ioContext);
    //udp::endpoint receiveEndpoint = *(resolver.resolve(udp::v4(), argv[1], "daytime").begin());
    udp::endpoint receiveEndpoint = *(resolver.resolve(udp::v4(), argv[1], "20013").begin());

    udp::socket socket(ioContext);
    socket.open(udp::v4());

    char sendBuf[1] = {0};
    socket.send_to(asio::buffer(sendBuf),receiveEndpoint);

    char recvBuf[1024] = {};
    udp::endpoint senderEndpoint;
    size_t len = socket.receive_from(asio::buffer(recvBuf), senderEndpoint);

    std::cout.write(recvBuf, len);

  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }


  return 0;
}
