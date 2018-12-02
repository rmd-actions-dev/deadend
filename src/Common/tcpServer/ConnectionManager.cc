#include "ConnectionManager.hh"

#include <ostream>
#include <fstream>

ConnectionManager::ConnectionManager(boost::asio::io_service &io) :
  m_io(io) {
  std::cout << *this << ": Created." << std::endl;
}

ConnectionManager::~ConnectionManager() {
  std::cout << *this << ": Destroyed." << std::endl;
}
 
void ConnectionManager::openConnection(TcpConnection::ConnectionPtr connection) {
	// Start the connection
  connection->start();
  // Manage it
  m_connections.push_back(connection);
}
void ConnectionManager::closeConnection(TcpConnection::ConnectionPtr connection) {
  // Find our connection
  std::vector<TcpConnection::ConnectionPtr>::iterator it = m_connections.begin();
  // Find the connection to remove
  for (; it != m_connections.end(); it++) {
    if (*it == connection) {
      m_connections.erase(it);
      break;
    }
  }

}
