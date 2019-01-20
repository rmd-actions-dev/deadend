#include "HttpServer.hh"
#include <iostream>

int main()
{
  try {
    HttpServer server("localhost", "12345");
    server.run();
  }
  catch (std::exception& e) {
   std::cout << e.what() << std::endl;
  }   
  return 0;
}

