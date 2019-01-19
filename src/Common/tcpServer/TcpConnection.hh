#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

class ConnectionManager;

class TcpConnection:
  public boost::enable_shared_from_this<TcpConnection>
{

public:
  typedef boost::shared_ptr<TcpConnection> ConnectionPtr;
 
  TcpConnection(
      boost::asio::io_service &io,
      ConnectionManager &manager);

  boost::asio::ip::tcp::socket& getSocket();

  void start();
  void stop();

private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const TcpConnection &) {
    return out << "TcpConnection";
  }

  void prv_handleRead(const boost::system::error_code&, size_t);
  void prv_handleWrite(const boost::system::error_code&, size_t);


  // Member Variables
  ConnectionManager &m_connectionManager;
  boost::asio::ip::tcp::socket m_socket;
  boost::array<char, 8192> m_buffer;

};
