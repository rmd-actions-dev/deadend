#include "RequestHandler.hh"

#include <boost/algorithm/string.hpp>

#include "Request.hh"

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
  prv_parseRequest(message);
  m_connection->sendResponse(response);
}

bool RequestHandler::prv_parseRequest(std::string request) {
  std::vector<std::string> lines;

  boost::split(lines, request, boost::is_any_of("\r\n"));

  if (lines.empty()) {
    std::cout << *this << ": Empty request..." << std::endl;
    return false;
  }

  // Parse the request
  std::vector<std::string> requestLine;
  boost::split(requestLine, lines.at(0), boost::is_any_of(" "));

  // Should be 3 items long
  if (requestLine.size() < 3) {
    std::cout << *this << ": Invalid request line - " << lines.at(0) << std::endl;
    return false;
   }

  // Create a request object
  Request requestObj;

  // Set the method
  requestObj.setMethod(requestLine.at(0));
  // Set the path
  requestObj.setPath(requestLine.at(1));
  // Set the version
  requestObj.setVersion(requestLine.at(2));

  // Remove the request-line
  lines.erase(lines.begin());

  std::cout << *this << ": Rest of request: " << std::endl;
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    requestObj.setHeader(*it);
  }

  requestObj.dumpRequest();
  return true;
}
}
}
