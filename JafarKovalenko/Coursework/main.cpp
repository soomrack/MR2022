#include "server.h"
using namespace Coursework;

int main()
{
  Server server;
  server.start();
  server.acceptClients();

  return 0;
}
