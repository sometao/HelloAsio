
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include "asio.hpp"


void my_print_2(const asio::error_code& err, asio::steady_timer* t, int* count) {
  if (*count > 5) {
    return;
  }

  auto tid = std::this_thread::get_id();
  std::cout << "[" << tid << "] print [" << *count << "]" << std::endl;
  ++(*count);

  // t->expires_from_now(asio::chrono::seconds(1));
  t->expires_at(t->expiry() + asio::chrono::seconds(1));
  auto f = std::bind(my_print_2, std::placeholders::_1, t, count);
  t->async_wait(f);


  std::cout << "[" << tid << "] begin sleep before " << (*count) << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "[" << tid << "] end sleep before " << (*count) << std::endl;
}

void my_print_2a(asio::steady_timer* t, int* count) {
  if (*count > 5) {
    return;
  }

  auto tid = std::this_thread::get_id();
  std::cout << "[" << tid << "] print [" << *count << "]" << std::endl;
  ++(*count);

  // t->expires_from_now(asio::chrono::seconds(1));
  t->expires_at(t->expiry() + asio::chrono::seconds(1));
  auto f = std::bind(my_print_2, std::placeholders::_1, t, count);
  t->async_wait(f);


  std::cout << "[" << tid << "] begin sleep before " << (*count) << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "[" << tid << "] end sleep before " << (*count) << std::endl;
}

void my_print_2b() {

  std::cout << "hello"<< std::endl;
}


int main() {
  std::cout << "Hello, I am t3." << std::endl;

  asio::io_context io;
  asio::steady_timer timer(io, asio::chrono::seconds(0));

  int count = 0;

  std::cout << ". 0 ." << std::endl;

  std::cout << ". 1 ." << std::endl;
  auto f1 = std::bind(my_print_2, std::placeholders::_1, &timer, &count);
  auto f1a = std::bind(my_print_2a, &timer, &count);


  std::function<void(const asio::error_code&)> f2;
  f2 = [&timer, &count, &f2](const asio::error_code& e) -> void {
    if (count > 5) {
      return;
    }
    auto tid = std::this_thread::get_id();
    std::cout << "[" << tid << "] print [" << count << "]" << std::endl;
    ++(count);
    // t->expires_from_now(asio::chrono::seconds(1));
    timer.expires_at(timer.expiry() + asio::chrono::seconds(1));
    timer.async_wait(f2);
    std::cout << "[" << tid << "] begin sleep before " << count << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "[" << tid << "] end sleep before " << count << std::endl;
    return;
  };



  //timer.async_wait(f1);
  timer.async_wait(f1a);
  //timer.async_wait(my_print_2b);
  //timer.async_wait(f2);
  std::cout << ". 2 ." << std::endl;

  //io.run();

  std::thread t1([&io](){io.run(); std::cout << "t1 finished." << std::endl;});
  std::thread t2([&io](){io.run(); std::cout << "t2 finished." << std::endl;});
  std::thread t3([&io](){io.run(); std::cout << "t3 finished." << std::endl;});
  std::thread t4([&io](){io.run(); std::cout << "t4 finished." << std::endl;});
  t1.join();
  t2.join();
  t3.join();
  t4.join();
   

  std::cout << "ALL finish ." << std::endl;

  return 0;
}