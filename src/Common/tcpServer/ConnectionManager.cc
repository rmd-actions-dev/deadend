#include "ConnectionManager.hh"

#include <algorithm>
#include <boost/bind.hpp>

ConnectionManager::ConnectionManager() {
  std::cout << *this << ": Created." << std::endl;
}

ConnectionManager::~ConnectionManager() {
  std::cout << *this << ": Destroyed." << std::endl;
}
 
void ConnectionManager::openConnection(TcpConnection::ConnectionPtr connection) {
  // Manage it
  m_connections.insert(connection);
  // Start the connection
  connection->start();
}

void ConnectionManager::closeConnection(TcpConnection::ConnectionPtr connection) {
  // Remove it
  m_connections.erase(connection);
  // Stop the connection
  connection->stop();
}

void ConnectionManager::stopAllConnections() {
  std::for_each(
      m_connections.begin(),
      m_connections.end(),
      boost::bind(&TcpConnection::stop, _1));

  m_connections.clear();

}
