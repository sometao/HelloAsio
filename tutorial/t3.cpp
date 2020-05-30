
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include "asio.hpp"


void my_print_2(const asio::error_code& err, asio::steady_timer* t, int* count) {

  if( *count > 30) {
    return;
  }

  std::cout << "print [" << *count << "]" << std::endl;
  ++(*count);

  t->expires_from_now(asio::chrono::seconds(1));
  auto f = std::bind(my_print_2, std::placeholders::_1, t, count);
  t->async_wait(f);

  std::cout << "begin sleep before " << (*count) << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "end sleep before " << (*count) << std::endl;

}


int main() {
  std::cout << "Hello, I am t3." << std::endl;

  asio::io_context io;
  asio::steady_timer timer(io, asio::chrono::seconds(0));

  int count = 0;

  std::cout << ". 0 ." << std::endl;

  std::cout << ". 1 ." << std::endl;
  auto f = std::bind(my_print_2, std::placeholders::_1, &timer, &count);
  timer.async_wait(f);
  std::cout << ". 2 ." << std::endl;

  std::thread t1([&](){io.run();});
  std::thread t2([&](){io.run();});
  std::thread t3([&](){io.run();});
  std::thread t4([&](){io.run();});

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  std::cout << ". finish ." << std::endl;

  return 0;
}