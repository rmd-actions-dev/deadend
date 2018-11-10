#include "ServerMain.hh"

#include <iostream>

ServerMain::ServerMain(
          boost::filesystem::path path) :
  m_logFile(path) {
  std::cout << *this << ": Created." << std::endl;
}


ServerMain::~ServerMain() {
  m_logFile << *this << ": Destroyed." << std::endl;
}
