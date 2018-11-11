#include "ServerMain.hh"

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

#include <iostream>

ServerMain::ServerMain() {
  m_logFile.open("log.today");
  m_logFile << *this << ": Created." << std::endl;
}


ServerMain::~ServerMain() {
  m_logFile << *this << ": Destroyed." << std::endl;
  m_logFile.close();
}

void ServerMain::doStuff() {
  std::cout << "HOLA" << std::endl;
}
