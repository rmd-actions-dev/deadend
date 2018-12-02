#include <iostream>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include "TcpConnection.hh"

class ConnectionManager: 
  private boost::noncopyable
{
public:
  ConnectionManager(boost::asio::io_service &io);
  virtual ~ConnectionManager();
 
 void openConnection(TcpConnection::ConnectionPtr); 
 void closeConnection(TcpConnection::ConnectionPtr); 

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const ConnectionManager &) {
    return out << "ConnectionManager";
  }

 std::vector<TcpConnection::ConnectionPtr> m_connections;
 boost::asio::io_service& m_io;
};
