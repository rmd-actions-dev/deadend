#include "TcpServer.hh"

TcpServer::TcpServer(boost::asio::io_service& io, uint16_t port) : 
    m_acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
  m_logFile.open("log.today");
  m_logFile << *this << ": Created." << std::endl;
  
  // Start handling requests
  prv_startAccept(); 
}

TcpServer::~TcpServer() {
  m_logFile << *this << ": Destroyed." << std::endl;
  m_logFile.close();
}

void TcpServer::prv_startAccept() {
  TcpConnection::ConnectionPtr newConnection = 
    TcpConnection::create(m_acceptor.get_io_service());

  m_acceptor.async_accept(
    *newConnection->getSocket(),
    boost::bind(&TcpServer::prv_handleAccept, 
                this, 
                newConnection,
                boost::asio::placeholders::error));
 
  m_logFile << *this << ": Waiting for a connection." << std::endl;
}


void TcpServer::prv_handleAccept(TcpConnection::ConnectionPtr newConnection,
                                 const boost::system::error_code& error) {
  // Check for errors
  if (!error) {
    m_logFile << *this << ": Accepted a connection." << std::endl;
    // Start the connection
    newConnection->start();
  }
  prv_startAccept();
}
