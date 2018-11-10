#include "ServerMain.hh"
#include <boost/filesystem/fstream.hpp>

int main()
{
  boost::filesystem::path p("log.today");
  ServerMain app(p); 
}

