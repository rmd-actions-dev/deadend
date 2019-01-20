#include "RequestHandler.hh"
namespace deadend {
namespace httpServer {

RequestHandler::RequestHandler(
    deadend::httpServer::TcpConnection::TcpConnectionPtr ptr) :
    m_connection(ptr) {
  std::cout << *this << ": Created." << std::endl;
}
RequestHandler::~RequestHandler() {
  std::cout << *this << ": Destroyed." << std::endl;

}

void RequestHandler::handleRequest(std::string message) {
  std::cout << *this << ": Handling request." << std::endl;
  std::string response = "HTTP GET";
  m_connection->sendResponse(response);
}

}
}
