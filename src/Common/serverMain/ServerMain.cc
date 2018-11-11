#include "ServerMain.hh"


#include <iostream>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


ServerMain::ServerMain() {
  m_logFile.open("log.today");
  m_logFile << *this << ": Created." << std::endl;
}


ServerMain::~ServerMain() {
  m_logFile << *this << ": Destroyed." << std::endl;
  m_logFile.close();
}

void ServerMain::doStuff() {
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.wait();

  std::cout << "Hello, world!" << std::endl;

}
