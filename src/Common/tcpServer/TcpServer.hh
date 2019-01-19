#pragma once

#include <fstream>
#include <ostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "TcpConnection.hh"
#include "ConnectionManager.hh"

class TcpServer {
public:
  TcpServer(
      std::string address,
      std::string port);
  virtual ~TcpServer();

  void run();

private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const TcpServer &) {
    return out << "TcpServer";
  }

  void prv_startAccept();
  void prv_handleAccept(const boost::system::error_code& error);
  void prv_handleStop();

  // Member variables
  boost::asio::io_service m_ioService;
  boost::asio::signal_set m_signals;
  boost::asio::ip::tcp::acceptor m_acceptor;
  ConnectionManager m_connectionManager;
  TcpConnection::ConnectionPtr m_newConnection;
  std::ofstream m_logFile;
};
