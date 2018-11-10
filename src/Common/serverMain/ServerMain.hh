#pragma once

#include <ostream>
#include <boost/filesystem/fstream.hpp>

class ServerMain
 {
public:
  ServerMain(
          boost::filesystem::path path
            );
  virtual ~ServerMain();

private:
  // Logging output operator
  friend std::ostream &operator<<(std::ostream &out, const ServerMain &) {
    return out << "ServerMain";
  }

  boost::filesystem::ofstream m_logFile;
};
