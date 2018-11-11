#include "ServerMain.hh"

int main()
{
  ServerMain* app = new ServerMain();
  app->doStuff();
  delete(app);
  return 0;
}

