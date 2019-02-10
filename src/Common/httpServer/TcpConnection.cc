#include "TcpConnection.hh"

#include <iostream>
#include <string>

#include "RequestHandler.hh"
#include <tcpServer/ConnectionManager.hh>

namespace deadend {
namespace httpServer {

TcpConnection::TcpConnection(
    boost::asio::io_service &io,
    deadend::tcpServer::ConnectionManager &manager) :
    deadend::tcpServer::TcpConnection(io, manager) {
  std::cout << *this << ": Created." << std::endl;
}

void TcpConnection::consumeData(std::string &buffer, size_t bytes) {
  std::cout << "=======================================" << std::endl
            << "IN --> HTTP" << std::endl
            << "=======================================" << std::endl
            << buffer << std::endl;
  deadend::httpServer::RequestHandler handler(boost::static_pointer_cast<TcpConnection>(shared_from_this()));
  handler.handleRequest(buffer);
  return;
}

}
}


