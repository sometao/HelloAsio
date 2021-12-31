
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include "asio.hpp"


class Printer {
 private:
  asio::steady_timer timer;
  int count;

  void print() {
    if(count > 6) {
      return;
    }
    std::cout << "print:[" << count << "]" << std::endl;
    count++;
    //timer.expires_from_now(asio::chrono::seconds(1));
    timer.expires_at(timer.expiry() + asio::chrono::seconds(1));
    timer.async_wait(std::bind(&Printer::print, this));
  }

 public:
  Printer(asio::io_context& io) : timer(io, asio::chrono::seconds(1)), count(0) {
    timer.async_wait(std::bind(&Printer::print, this));
  }

  ~Printer() { std::cout << "Final count is " << count << std::endl; }
};


int main() {
  std::cout << "Hello, I am t4." << std::endl;

  asio::io_context io;
  Printer printer(io);

  std::cout << ". 1 ." << std::endl;

  io.run();

  std::cout << ". finish ." << std::endl;

  return 0;
}