#pragma once
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "TcpConnection.hh"

class RequestHandler {

public:
  RequestHandler(TcpConnection::TcpConnectionPtr ptr);
  ~RequestHandler();

  void handleRequest(std::string message);

private:
  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const RequestHandler &) {
    return out << "RequestHandler";
  }

  // Member variables
  TcpConnection::TcpConnectionPtr m_connection;
};
