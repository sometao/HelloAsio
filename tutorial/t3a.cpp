

#include <iostream>
#include <string>
#include <thread>
#include "asio.hpp"


void my_handler(const asio::error_code& e, asio::steady_timer* t) {
  std::cout << "my_handler: Hello, world!  begin." << std::endl;
  t->expires_from_now(std::chrono::milliseconds(500));
  auto func = std::bind(my_handler, std::placeholders::_1, t);
  t->async_wait(func);
}


int main() {
  std::cout << "Hello, I am t2." << std::endl;

  asio::io_context io;
  asio::steady_timer t(io, asio::chrono::seconds(3));


  std::cout << ". 1 ." << std::endl;
  t.async_wait(std::bind(my_handler, std::placeholders::_1, &t));

  std::thread t1([&]() {
    std::cout << "lambda begin. 1" << std::endl;
    io.run();  // wait/block here.
    std::cout << "lambda done.  1" << std::endl;
  });

  std::thread t2([&]() {
    std::cout << "lambda begin.  2" << std::endl;
    io.run();  // wait/block here.
    std::cout << "lambda done.  2" << std::endl;
  });

  std::thread t3([&]() {
    std::cout << "lambda begin. 3" << std::endl;
    io.run();  // wait/block here.
    std::cout << "lambda done.  3" << std::endl;
  });

  t1.join();
  t2.join();
  t3.join();

  std::cout << ". finish ." << std::endl;

  return 0;
}