#include "TcpConnection.hh"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>

// Get the socket
boost::shared_ptr<boost::asio::ip::tcp::socket> TcpConnection::getSocket() {
  return m_socket;
}

TcpConnection::TcpConnection(boost::asio::io_service &io) {
  std::cout << "Creating a new TCP connection object." << std::endl;
  m_socket.reset(new boost::asio::ip::tcp::socket(io));
}

// Start the TCP connection
void TcpConnection::start() {

  // Read from the socket
 m_socket->async_read_some(boost::asio::buffer(m_data, maxSize),
                           boost::bind(
                           &TcpConnection::prv_handleRead, 
                           shared_from_this(),
                           boost::asio::placeholders::error,
                           boost::asio::placeholders::bytes_transferred));
}

  
void TcpConnection::prv_handleRead(const boost::system::error_code& error, size_t bytes) {
  std::cout << "Read " << bytes << " bytes." << std::endl;
  if (!error) {
    boost::asio::async_write(			
      *m_socket, 
      boost::asio::buffer(m_data, bytes),
      boost::bind(&TcpConnection::prv_handleWrite, 
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
  }
  else {
    std::cout << "Encountered an error(" << error.value() << ':' << error.message() << ')' << std::endl;
  }
}

void TcpConnection::prv_handleWrite(const boost::system::error_code& error, size_t bytes) {
  std::cout << "Writing " << bytes << " bytes." << std::endl;
  if (!error) {
    m_socket->async_read_some(boost::asio::buffer(m_data, bytes),
                              boost::bind(
                              &TcpConnection::prv_handleRead, 
                              shared_from_this(),
                              boost::asio::placeholders::error,
                              boost::asio::placeholders::bytes_transferred));
  } 
  else {
    std::cout << "Encountered an error(" << error.value() << ':' << error.message() << ')' << std::endl;
  }
}


