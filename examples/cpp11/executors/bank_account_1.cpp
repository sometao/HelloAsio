#include <sdkddkver.h>

#include <asio/execution.hpp>
#include <asio/static_thread_pool.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using asio::static_thread_pool;
namespace execution = asio::execution;

// Traditional active object pattern.
// Member functions do not block.

class bank_account {
  int balance_ = 0;
  //mutable static_thread_pool pool_{2};
  mutable static_thread_pool pool_{2};

 public:
  void deposit(int amount) {
    execution::execute(pool_.executor(), [this, amount] {
      auto tid = std::this_thread::get_id();
      std::cout << "deposit " << amount << " in t[" << tid << "]" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(2800));
      balance_ += amount;
    });
  }

  void withdraw(int amount) {
    execution::execute(pool_.executor(), [this, amount] {
      auto tid = std::this_thread::get_id();
      std::cout << "withdraw " << amount << " in t[" << tid << "]" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1050));
      if (balance_ >= amount)
        balance_ -= amount;
      else
        std::cout << "No enough balance." << std::endl;
    });
  }

  void print_balance() const {
    execution::execute(pool_.executor(),
                       [this] { std::cout << "balance = " << balance_ << "\n"; });
  }

  ~bank_account() { pool_.wait(); }
};

int main() {
  auto tid = std::this_thread::get_id();
  bank_account acct;
  //std::this_thread::sleep_for(std::chrono::milliseconds(500));
  acct.deposit(11);
  std::cout << "main t[" << tid << "] -----------  1  ---------- " << std::endl;
  acct.withdraw(12);
  std::cout << "main t[" << tid << "] -----------  2  ---------- " << std::endl;
  acct.deposit(23);
  std::cout << "main t[" << tid << "] -----------  3  ---------- " << std::endl;
  acct.withdraw(14);
  std::cout << "main t[" << tid << "] -----------  4  ---------- " << std::endl;
  acct.deposit(25);
  std::cout << "main t[" << tid << "] -----------  5  ---------- " << std::endl;
  acct.withdraw(16);
  std::cout << "main t[" << tid << "] -----------  6  ---------- " << std::endl;
  acct.print_balance();
  std::cout << "main t[" << tid << "] -----------  7  ---------- " << std::endl;
}
