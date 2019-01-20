#pragma once

#include "TcpConnection.hh"
#include "ConnectionManager.hh"

#include "../tcpServer/TcpServer.hh"

class HttpServer {
public:
  HttpServer(
      std::string address,
      std::string port) {
    // Initialize the server
    m_server.reset(new TcpServer<TcpConnection, ConnectionManager>(address, port));
  }
  virtual ~HttpServer() {}

  void run() {
    // Start the server
    m_server->run();
  }

private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const HttpServer &) {
    return out << "HttpServer";
  }

  // Member variables
  boost::shared_ptr<TcpServer<TcpConnection, ConnectionManager>> m_server;
};
