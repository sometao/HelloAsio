#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>


using asio::ip::tcp;

std::string make_daytime_string() {
  using namespace std;  // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


 int main()
{
  try
  {
    asio::io_context ioContext;

    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 13));

    for(;;) {
      tcp::socket socket(ioContext);
      std::cout << "accepting..." << std::endl;
      acceptor.accept(socket);
      std::cout << "accepted" << std::endl;
      auto msg = make_daytime_string();
      asio::error_code ignored_error;
      std::cout << "writing msg:" << msg << std::endl;
      asio::write(socket, asio::buffer(msg.c_str(), msg.length()), ignored_error);
      std::cout << "write done, error:" << ignored_error.message() << std::endl;
    }

  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }

}

//int main() {
//  try {
//    asio::io_context io_context;
//
//    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));
//
//    for (;;) {
//      tcp::socket socket(io_context);
//      acceptor.accept(socket);
//
//      std::string message = make_daytime_string();
//
//      asio::error_code ignored_error;
//      asio::write(socket, asio::buffer(message, message.length()), ignored_error);
//    }
//  } catch (std::exception& e) {
//    std::cerr << e.what() << std::endl;
//  }
//
//  return 0;
//}
