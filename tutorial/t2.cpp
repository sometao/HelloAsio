

#include <iostream>
#include <string>
#include <thread>
#include "asio.hpp"


void my_handler(const asio::error_code& e) {
  std::cout << "my_handler: Hello, world!  begin." << std::endl;
  auto v = e.value();
  auto m = e.message();
  std::this_thread::sleep_for(asio::chrono::seconds(5));
  std::cout << "my_handler: Hello, world!   end. v="<< v << ", m=" << m << std::endl;
}


void my_handler2(const asio::error_code& e) {
  std::cout << "Hi, I'm heander [ 2 ]" << std::endl;
}

void my_handler3(const asio::error_code& e) {
  std::cout << "Hi, I'm heander [ 3 ]" << std::endl;
}


int main() {
  std::cout << "Hello, I am t2." << std::endl;

  asio::io_context io;
  asio::steady_timer t(io, asio::chrono::seconds(3));

  std::cout << ". 0 ." << std::endl;
  std::this_thread::sleep_for(asio::chrono::seconds(1));

  std::cout << ". 1 ." << std::endl;
  t.async_wait(&my_handler2);
  std::cout << ". 2 ." << std::endl;
  t.async_wait(&my_handler);
  std::cout << ". 3 ." << std::endl;
  t.async_wait(&my_handler3);
  std::cout << ". 4 ." << std::endl;


  //io.run();

  std::thread work([&]() {
    std::cout << "lambda begin." << std::endl;
    io.run(); // wait/block here.
    std::cout << "lambda done." << std::endl;
  });

  std::cout << ". begin join ." << std::endl;
  work.join();

  std::cout << ". finish ." << std::endl;

  return 0;
}