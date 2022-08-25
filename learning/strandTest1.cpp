#include "config.h"
#include "seeker/logger.h"
#include <iostream>
#include <string>

#include "asio.hpp"


using asio::ip::udp;


int main(int argc, char* argv[]) {
  seeker::Logger::init();
  try {
//    asio::io_context io;
//    udp::socket socket1(io);
//    asio::strand<asio::io_context::executor_type> strand1;
//
//    udp::endpoint epoint;
//
//    socket1.async_send_to(asio::buffer("abc", 123), epoint,
//                          [](std::error_code ec, std::size_t len) { return; });
//
//    socket1.async_send_to(
//        asio::buffer("abc", 123), epoint,
//        asio::bind_executor(strand1, [](std::error_code ec, std::size_t len) { return; }));
//
//    asio::strand<asio::io_context::executor_type> strand2(asio::make_strand(io));
//    udp::socket socket2(strand2);
//
//

  } catch (std::exception ex) {
    E_LOG("Got a exception: {}", ex.what());
  }
  return 0;
}
