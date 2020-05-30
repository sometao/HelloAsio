

#include <iostream>
#include <string>
#include "asio.hpp"
#include <chrono>

int main() {

  std::cout << "Hello, asio." << std::endl;

  asio::io_context io;
  asio::io_context ioo;
  asio::steady_timer t(io, asio::chrono::seconds(5));

  std::cout << "1" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(4));
  std::cout << "2" << std::endl;

  t.wait();
  
  std::cout << "Hello, world." << std::endl;
  return 0;


}