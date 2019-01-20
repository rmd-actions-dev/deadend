#include "TcpConnection.hh"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include "ConnectionManager.hh"
#include "RequestHandler.hh"

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

  // Start reading
  prv_readSome();
}

void TcpConnection::stop() {
  std::cout << *this << ": Closing connection." << std::endl;

  // Close the socket
  m_socket.close();
}

  
void TcpConnection::consumeData(std::string &buffer, size_t bytes) {
  std::cout << *this << ": Request content: " << std::endl << buffer << std::endl;
  RequestHandler handler(shared_from_this());
  handler.handleRequest(buffer);
  return;
}

void TcpConnection::sendResponse(std::string &buffer) {
  std::cout << *this << ": Response content: " << std::endl << buffer << std::endl;

  boost::asio::async_write(
    m_socket,
    boost::asio::buffer(buffer),
    boost::bind(&TcpConnection::prv_handleWrite,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::prv_handleRead(const boost::system::error_code& error, size_t bytes) {
  std::cout << *this << ": Read " << bytes << " bytes." << std::endl;
  if (!error) {
    std::string buffer(m_readBuffer.begin(), m_readBuffer.begin() + bytes);

    // This will be overridden by the libraries
    consumeData(buffer, bytes);

    // Read moar
    prv_readSome();
    return;
  }
  else {
    std::cout << *this << ": Encountered an error(" << error.value() << ':' << error.message() << ')' << std::endl;
    m_connectionManager.closeConnection(shared_from_this());
  }
}

void TcpConnection::prv_handleWrite(const boost::system::error_code& error, size_t bytes) {
  std::cout << *this << ": Writing " << bytes << " bytes." << std::endl;
  if (!error) {


  } 
  else {
    std::cout << *this << ": Encountered an error(" << error.value() << ':' << error.message() << ')' << std::endl;
    m_connectionManager.closeConnection(shared_from_this());
  }
}

void TcpConnection::prv_readSome() {
  std::cout << *this << ": Reading some data." << std::endl;

  // Read from the socket
  m_socket.async_read_some(boost::asio::buffer(m_readBuffer),
                           boost::bind(
                             &TcpConnection::prv_handleRead,
                             shared_from_this(),
                             boost::asio::placeholders::error,
                             boost::asio::placeholders::bytes_transferred));
}


