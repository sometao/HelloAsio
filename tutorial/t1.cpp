

#include <iostream>
#include <string>
#include "asio.hpp"
#include <chrono>

int main() {

  std::cout << "Hello, I am t1." << std::endl;

  asio::io_context io;
  asio::steady_timer t(io, asio::chrono::seconds(5));

  std::cout << "1" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  //std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "2" << std::endl;

  t.wait();
  
  std::cout << "Hello, world." << std::endl;
  return 0;


}