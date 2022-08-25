
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <chrono>
#include "asio.hpp"


class Printer {
 private:
  asio::strand<asio::io_context::executor_type> strand_;
  asio::steady_timer timer1;
  asio::steady_timer timer2;
  int count;

  void print1() {
    if(count > 20 ) {
      return;
    }
    auto tid = std::this_thread::get_id();

    std::cout << "[" << tid << "] print1 :[" << count << "]" << std::endl;
    count++;
    timer1.expires_from_now(asio::chrono::seconds(1));

    //timer1.async_wait(std::bind(&Printer::print1, this));
    timer1.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print1, this)));

    std::cout << "[" << tid << "] print1 sleep begin" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[" << tid << "] print1 sleep end" << std::endl;
  }

  void print2() {
    if(count > 20 ) {
      return;
    }
    auto tid = std::this_thread::get_id();

    std::cout << "[" << tid << "] print2 :[" << count << "]" << std::endl;
    count++;
    timer2.expires_at(timer2.expiry() + asio::chrono::seconds(1));

    //timer2.async_wait(std::bind(&Printer::print2, this));
    auto ex = asio::bind_executor(strand_, std::bind(&Printer::print2, this));
    timer2.async_wait(ex);

    std::cout << "[" << tid << "] print2 sleep begin" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[" << tid << "] print2 sleep end" << std::endl;
  }

 public:
  Printer(asio::io_context& io)
      : strand_(asio::make_strand(io)),
        timer1(io, asio::chrono::seconds(1)),
        timer2(io, asio::chrono::seconds(1)),
        count(0) {
    //timer1.async_wait(std::bind(&Printer::print1, this));
    //timer2.async_wait(std::bind(&Printer::print2, this));
    timer1.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print1, this)));
    timer2.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print2, this)));
  }

  ~Printer() { std::cout << "Final count is " << count << std::endl; }
};

void foo(int a) { std::cout << a << std::endl; }

int main() {
  std::cout << "Hello, I am t5." << std::endl;

  asio::io_context io;
  Printer printer(io);

  std::cout << ". 1 ." << std::endl;



  std::thread t1( [&]() { io.run(); } );
  std::thread t2( [&]() { io.run(); } );
  std::thread t3( [&]() { io.run(); } );
  //std::thread t4( [&]() { io.run(); } );

  std::cout << ". 2 ." << std::endl;
  //io.run();
  std::cout << ". 3 ." << std::endl;
  t1.join();
  t2.join();
  t3.join();
  //t4.join();
  std::cout << ". finish ." << std::endl;

  return 0;
}