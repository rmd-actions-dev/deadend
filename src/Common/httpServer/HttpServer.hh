#pragma once

#include <tcpServer/TcpServer.hh>
#include "TcpConnection.hh"


namespace deadend {
namespace httpServer {

class HttpServer {
public:
  HttpServer(
      std::string address,
      std::string port) {
    // Initialize the server
    m_server.reset(new deadend::tcpServer::TcpServer<deadend::httpServer::TcpConnection,deadend::tcpServer::ConnectionManager>(address, port));
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
  boost::shared_ptr<deadend::tcpServer::TcpServer<deadend::httpServer::TcpConnection, deadend::tcpServer::ConnectionManager>> m_server;
};

}
}
