#include <iostream>
#include <vector>
#include "asio.hpp"


using asio::ip::tcp;

int main(int argc, char* argv[])  {


  try {
  
    if(argc != 2) {
      std::cout << "Usage: client <host>" << std::endl;
    }

    asio::io_context ioContext;
    tcp::resolver resolver(ioContext);
    auto endpoints = resolver.resolve(argv[1], "daytime");
    tcp::socket socket(ioContext);

    std::cout << "connecting..." << std::endl;
    asio::connect(socket, endpoints);
    std::cout << "connected" << std::endl;


    for(;;) {
      std::vector<char> buf(1024);
      //char buf[1024];
      asio::error_code error;
      std::cout << "reading..." << std::endl;
      size_t len = socket.read_some(asio::buffer(buf), error);
      std::cout << "read len=" << len << std::endl;

      if(error == asio::error::eof) {
        break;
      } else if (error) {
        throw asio::system_error(error);
      }
      std::cout.write(buf.data(), len);
    }

  } catch (std::exception ex) {
    std::cerr << ex.what() << std::endl;
  }


}