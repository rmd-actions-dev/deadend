#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>

namespace deadend {
namespace tcpServer {

class ConnectionManager;

class TcpConnection:
  public  boost::enable_shared_from_this<TcpConnection>,
  private boost::noncopyable
{

public:
  typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
 
  TcpConnection(
      boost::asio::io_service &io,
      deadend::tcpServer::ConnectionManager &manager);

  virtual ~TcpConnection() {}

  virtual boost::asio::ip::tcp::socket& getSocket();

  virtual void start();
  virtual void stop();

  // This should be overridden by any library than inherits from tcpServer
  virtual void consumeData(std::string &buffer, size_t bytes);

  virtual void sendResponse(std::string &buffer);


protected:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const TcpConnection &) {
    return out << "TcpConnection";
  }

  virtual void pro_handleRead(const boost::system::error_code&, size_t);
  virtual void pro_handleWrite(const boost::system::error_code&, size_t);
  virtual void pro_readSome();

  // Member Variables
  deadend::tcpServer::ConnectionManager &m_connectionManager;
  boost::asio::ip::tcp::socket m_socket;
  boost::array<char, 65535> m_readBuffer;
  std::string m_writeBuffer;
};

}
}
