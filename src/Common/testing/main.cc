//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

std::string getDaytimeString() {
  std::time_t now = std::time(0);
  return std::ctime(&now);

}
int main()
{
  try {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, 
                                           boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8008));
    for (;;) {  
      boost::asio::ip::tcp::socket socket(io_service);
      acceptor.accept(socket);

      std::string message = getDaytimeString();

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
