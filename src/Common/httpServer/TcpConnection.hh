#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>

class ConnectionManager;

class TcpConnection:
  public  boost::enable_shared_from_this<TcpConnection>,
  private boost::noncopyable
{

public:
  typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
 
  TcpConnection(
      boost::asio::io_service &io,
      ConnectionManager &manager);
  virtual ~TcpConnection() {}

  boost::asio::ip::tcp::socket& getSocket();

  void start();
  void stop();

  // This should be overridden by any library than inherits from tcpServer
  virtual void consumeData(std::string &buffer, size_t bytes);

  void sendResponse(std::string &buffer);


private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const TcpConnection &) {
    return out << "TcpConnection";
  }

  void prv_handleRead(const boost::system::error_code&, size_t);
  void prv_handleWrite(const boost::system::error_code&, size_t);
  void prv_readSome();

  // Member Variables
  ConnectionManager &m_connectionManager;
  boost::asio::ip::tcp::socket m_socket;
  boost::array<char, 65535> m_readBuffer;
  std::string m_writeBuffer;
};
