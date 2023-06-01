#include "server.h"
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

Coursework::Server::Server(uint16_t port, const std::string& ip)
    : port(port), ip(ip)
{
  try
  {
    descriptor = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);  // set NONBLOCK flag
    if (descriptor == -1)
      throw std::string{"Server socket establishment error.\n"};
    else
      std::cout << "Server socket setup succeeded.\n";
  }
  catch (std::string& exception)
  {
    std::cerr << exception;
    exit(-1);
  }

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  if (ip.empty())
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // 0.0.0.0, accept any connections
  else
    inet_aton(ip.data(), &serverAddr.sin_addr);  // convert ip to binary form (network byte order)

  setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR,  // reuse addres
             reinterpret_cast<socklen_t*>(1), sizeof(int));
  setsockopt(descriptor, SOL_SOCKET, SO_REUSEPORT,
             reinterpret_cast<socklen_t*>(1), sizeof(int));  // reuse port

  try
  {
  bool isBindFailed = bind(descriptor, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));

  if (isBindFailed) throw std::string{"Server socket binding error. Server socket closed. Exit...\n"};
  else
    std::cout << "Server binding to " <<
              (ip.empty() ? "127.0.0.1" : ip) << ":" << port << " sucessful.\n";
  }
  catch (std::string& exception)
  {
    std::cerr << exception;
    exit(-1);
  }
  worker.setServerEvent(descriptor);
}

Coursework::Server::~Server() noexcept
{
  bool isCloseFailed = close(descriptor);
  if (isCloseFailed)
    std::cerr << "Server socket closing error.\n";
  else
    std::cout << "Server socket closing succeeded.\n";
}

void Coursework::Server::start(uint16_t connections) const
{
  try
  {
  bool isListenFailed = listen(descriptor, connections);
  if (isListenFailed) throw std::string{"Server socket listening error. Exit...\n"};
  else
    std::cout << "Server socket listening succeeded.\n";
  }
  catch (std::string& exception)
  {
    std::cerr << exception;
    exit(-1);
  }
}

void Coursework::Server::acceptClients()
{
  while (true)
  {
    int16_t events = worker.waitForEvents();
    worker.eventsHandling(events);
  }
}
