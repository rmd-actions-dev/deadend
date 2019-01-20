#pragma once
#include <tcpServer/TcpConnection.hh>


namespace deadend {
namespace httpServer {

class TcpConnection:
  public deadend::tcpServer::TcpConnection
{

public:
  typedef boost::shared_ptr<deadend::httpServer::TcpConnection> TcpConnectionPtr;

  TcpConnection(
      boost::asio::io_service &io,
      deadend::tcpServer::ConnectionManager &manager);

  // This should be overridden by any library than inherits from tcpServer
  void consumeData(std::string &buffer, size_t bytes);
};

}
}
