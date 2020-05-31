#include <iostream>
#include <memory>
#include <vector>
#include "asio.hpp"


using asio::ip::udp;

std::string make_daytime_string() {
  using namespace std;  // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


class UdpServer {
 private:
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::vector<char> recvBuf;

  void handle_send(std::shared_ptr<std::string> /*message*/,
                   const asio::error_code& /*error*/,
                   std::size_t /*bytes_transferred*/) {}

  void handle_receive(std::error_code error, std::size_t len) {
    if (!error) {
      auto msg = std::make_shared<std::string>(make_daytime_string());

      socket_.async_send_to(
          asio::buffer(*msg), remote_endpoint_,
          [this, msg](std::error_code ec, std::size_t len) { handle_send(msg, ec, len); });

      start_receive();
    }
  }

  void start_receive() {
    socket_.async_receive_from(
        asio::buffer(recvBuf), remote_endpoint_,
        [this](std::error_code ec, std::size_t len) { handle_receive(ec, len); });
  }

 public:
  UdpServer(asio::io_context& ioContext)
      : socket_(ioContext, udp::endpoint(udp::v4(), 13)), recvBuf(1024) {
    start_receive();
  }
};



int main(int argc, char* argv[]) {
  try {
    asio::io_context ioContext;
    UdpServer server(ioContext);
    ioContext.run();
  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}