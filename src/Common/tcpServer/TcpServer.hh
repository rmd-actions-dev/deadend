#pragma once

#include <fstream>
#include <ostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "TcpConnection.hh"

class TcpServer {
public:
  TcpServer(boost::asio::io_service &io, uint16_t port);
  virtual ~TcpServer();
private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const TcpServer &) {
    return out << "TcpServer";
  }

  void prv_startAccept();
  void prv_handleAccept(TcpConnection::ConnectionPtr newConnection,
                        const boost::system::error_code& error);

  // Member variables
  boost::asio::ip::tcp::acceptor m_acceptor;
  std::ofstream m_logFile;
};
