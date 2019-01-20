#pragma once
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "TcpConnection.hh"

namespace deadend {
namespace httpServer {

class RequestHandler {

public:
  RequestHandler(deadend::httpServer::TcpConnection::TcpConnectionPtr ptr);
  ~RequestHandler();

  void handleRequest(std::string message);

private:
  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const RequestHandler &) {
    return out << "RequestHandler";
  }

  // Member variables
  deadend::httpServer::TcpConnection::TcpConnectionPtr m_connection;
};

}
}
