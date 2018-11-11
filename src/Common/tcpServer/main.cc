#include "TcpServer.hh"
#include <boost/asio.hpp>
#include <iostream>

int main()
{
  try {
    boost::asio::io_service io;
    TcpServer server(io, 8008);
    io.run();
  }
  catch (std::exception& e) {
   std::cout << e.what() << std::endl;
  }   
  return 0;
}

