#pragma once

#include <fstream>
#include <ostream>

class ServerMain {
public:
  ServerMain();
  virtual ~ServerMain();
  void doStuff();
private:
  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const ServerMain &) {
    return out << "ServerMain";
  }

  std::ofstream m_logFile;
};
