#pragma once

#include <fstream>
#include <ostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <signal.h>

template <class Connection, class Manager>
class TcpServer {

public:
  typedef boost::shared_ptr<Connection> ConnectionPtr;

public:
  TcpServer(
      std::string address,
      std::string port):
        m_ioService(),
        m_signals(m_ioService),
        m_acceptor(m_ioService),
        m_connectionManager(),
        m_newConnection() {
      m_logFile.open("log.today");
      std::cout << *this << ": Created." << std::endl;

      // Do signal stuff
      m_signals.add(SIGINT);
      m_signals.add(SIGTERM);

      m_signals.async_wait(boost::bind(&TcpServer::prv_handleStop, this));

      // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
      boost::asio::ip::tcp::resolver resolver(m_ioService);
      boost::asio::ip::tcp::resolver::query query(address, port);
      boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

      m_acceptor.open(endpoint.protocol());
      m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
      m_acceptor.bind(endpoint);
      m_acceptor.listen();

      // Start handling requests
      prv_startAccept();
  }

  virtual ~TcpServer() {
    std::cout << *this << ": Destroyed." << std::endl;
    m_logFile.close();
  }

  void run() {
    // Start up the io service
    m_ioService.run();
  }

private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const TcpServer &) {
    return out << "TcpServer";
  }

  void prv_startAccept() {
    // Created the new connection object
    m_newConnection.reset(
        new Connection(
            m_ioService,
            m_connectionManager));

    m_acceptor.async_accept(
      m_newConnection->getSocket(),
      boost::bind(&TcpServer::prv_handleAccept,
                  this,
                  boost::asio::placeholders::error));

    std::cout << *this << ": Waiting for a connection." << std::endl;
  }

  void prv_handleAccept(const boost::system::error_code& error) {
    if (!m_acceptor.is_open()) {
      // If the server was stopped by a signal
      return;
    }
    // Check for errors
    if (!error) {
      std::cout << *this << ": Accepted a connection." << std::endl;
      // Start the connection
      m_connectionManager.openConnection(m_newConnection);
    }
    prv_startAccept();
  }

  void prv_handleStop() {
    std::cout << *this << ": Stopping the server." << std::endl;
    // Stop accepting connections
    m_acceptor.close();
    // Close all existing connections
    m_connectionManager.stopAllConnections();
  }

  // Member variables
  boost::asio::io_service m_ioService;
  boost::asio::signal_set m_signals;
  boost::asio::ip::tcp::acceptor m_acceptor;
  Manager m_connectionManager;
  ConnectionPtr m_newConnection;
  std::ofstream m_logFile;
};
