#include "TcpConnection.hh"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>

// Get the socket
boost::asio::ip::tcp::socket& TcpConnection::getSocket() {
  return m_socket;
}

TcpConnection::TcpConnection(boost::asio::io_service &io) :
  m_socket(io) {
  std::cout << "Creating a new TCP connection object." << std::endl;
}

// Start the TCP connection
void TcpConnection::start() {
  std::time_t now = std::time(0);
  m_message = std::ctime(&now);
 
  // Write our message
  boost::asio::async_write(
    m_socket, 
    boost::asio::buffer(m_message),
    boost::bind(&TcpConnection::prv_handleWrite, 
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}
  
void TcpConnection::prv_handleWrite(const boost::system::error_code&, size_t bytes) {
  std::cout << "Writing " << bytes << " bytes." << std::endl;
}


