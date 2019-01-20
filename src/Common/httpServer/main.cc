#include "HttpServer.hh"
#include <iostream>

int main()
{
  try {
    deadend::httpServer::HttpServer server("localhost", "12345");
    server.run();
  }
  catch (std::exception& e) {
   std::cout << e.what() << std::endl;
  }   
  return 0;
}

