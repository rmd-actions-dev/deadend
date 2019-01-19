#include "TcpServer.hh"
#include <iostream>

int main()
{
  try {
    TcpServer server("localhost", "8008");
    server.run();
  }
  catch (std::exception& e) {
   std::cout << e.what() << std::endl;
  }   
  return 0;
}

