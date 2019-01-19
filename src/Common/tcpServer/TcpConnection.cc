#include "TcpConnection.hh"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include "ConnectionManager.hh"

TcpConnection::TcpConnection(
    boost::asio::io_service &io,
    ConnectionManager &manager) :
    m_connectionManager(manager),
    m_socket(io) {
  std::cout << *this << ": Created." << std::endl;
}

// Get the socket
boost::asio::ip::tcp::socket& TcpConnection::getSocket() {
  return m_socket;
}

// Start the TCP connection
void TcpConnection::start() {
  std::cout << *this << ": Opening connection." << std::endl;

  // Read from the socket
  m_socket.async_read_some(boost::asio::buffer(m_buffer),
                           boost::bind(
                             &TcpConnection::prv_handleRead,
                             shared_from_this(),
                             boost::asio::placeholders::error,
                             boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::stop() {
  std::cout << *this << ": Closing connection." << std::endl;

  // Close the socket
  m_socket.close();
}

  
void TcpConnection::prv_handleRead(const boost::system::error_code& error, size_t bytes) {
  std::cout << *this << ": Read " << bytes << " bytes." << std::endl;
  if (!error) {
    std::cout << *this << ":" << std::endl << m_buffer.data() << std::endl;

    boost::asio::async_write(
      m_socket,
      boost::asio::buffer(m_buffer, bytes),
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
  std::cout << *this << ": Writing " << bytes << " bytes." << std::endl;
  if (!error) {
//    m_socket.async_read_some(boost::asio::buffer(m_buffer, bytes),
//                             boost::bind(
//                              &TcpConnection::prv_handleRead,
//                              shared_from_this(),
//                              boost::asio::placeholders::error,
//                              boost::asio::placeholders::bytes_transferred));

    boost::system::error_code unusedEC;
    // Close the connection
    m_socket.shutdown(
        boost::asio::ip::tcp::socket::shutdown_both,
        unusedEC);
  } 
  else {
    std::cout << *this << ": Encountered an error(" << error.value() << ':' << error.message() << ')' << std::endl;
    m_connectionManager.closeConnection(shared_from_this());
  }
}



