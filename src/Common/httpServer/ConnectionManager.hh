#include <iostream>
#include <set>

#include <boost/noncopyable.hpp>

#include "TcpConnection.hh"

class ConnectionManager: 
  private boost::noncopyable
{
public:
  ConnectionManager();
  virtual ~ConnectionManager();
 
 void openConnection(TcpConnection::TcpConnectionPtr);
 void closeConnection(TcpConnection::TcpConnectionPtr);
 void stopAllConnections();

private:

  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const ConnectionManager &) {
    return out << "ConnectionManager";
  }

 std::set<TcpConnection::TcpConnectionPtr> m_connections;
};
