
#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <asio.hpp>

using asio::ip::tcp;

std::string make_daytime_string() {
  using namespace std;  // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
 private:
  tcp::socket socket_;
  std::string message_;

  TcpConnection(asio::io_context& io_context) : socket_(io_context) {}

  void handle_write(const asio::error_code& /*error*/, size_t /*bytes_transferred*/) {
    std::cout << "------------------- TcpConnection handle_write begin" << std::endl;
    std::cout << "------------------- TcpConnection handle_write end" << std::endl;
  }

 public:
  typedef std::shared_ptr<TcpConnection> Pointer;

  static Pointer create(asio::io_context& io_context) {
    return Pointer(new TcpConnection(io_context));
  }

  tcp::socket& socket() { return socket_; }

  void start() {
    std::cout << "------------------- TcpConnection start begin" << std::endl;

    message_ = make_daytime_string();

    auto self(shared_from_this());

    asio::async_write(
        socket_, asio::buffer(message_),
        [this, self](std::error_code ec, std::size_t len) { handle_write(ec, len); });

    std::cout << "------------------- TcpConnection start end" << std::endl;
  };
};


class TcpServer {
 private:
  asio::io_context& io_context_;
  tcp::acceptor acceptor_;

  void handle_accept(TcpConnection::Pointer new_connection, const asio::error_code& error) {
    std::cout << "TcpServer handle_accept begin" << std::endl;
    if (!error) {
      new_connection->start();
    }
    start_accept();
    std::cout << "TcpServer handle_accept end" << std::endl;
  }

  void start_accept() {
    std::cout << "TcpServer start_accept begin" << std::endl;
    TcpConnection::Pointer new_connection = TcpConnection::create(io_context_);
    acceptor_.async_accept(
        new_connection->socket(),
        [this, new_connection](std::error_code ec) { handle_accept(new_connection, ec); });
    std::cout << "TcpServer start_accept end" << std::endl;
  }

 public:
  TcpServer(asio::io_context& io_context)
      : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 13)) {
    start_accept();
  }
};



int main() {
  try {
    asio::io_context io_context;
    TcpServer server(io_context);
    io_context.run();
  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }


  return 0;
}
