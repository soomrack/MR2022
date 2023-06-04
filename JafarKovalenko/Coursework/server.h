#ifndef COURSEWORK_SERVER_H
#define COURSEWORK_SERVER_H

#include <sys/socket.h>  // socket(), bind(), listen(), accept()
#include <netinet/in.h>  // sockaddr_in
#include <arpa/inet.h>   // inet_aton()
#include <csignal>       // close()
#include <cstdint>
#include <string>
#include "worker.h"


namespace Coursework
{
  class Server
  {
  public:
    explicit Server(uint16_t port = 11111, const std::string& ip = "");  // create server socket and bind it
    ~Server() noexcept;  // close socket
    void start(uint16_t connections = SOMAXCONN) const;  // start listening
    void acceptClients(); // start handling clients requests
    inline int32_t getDescriptor() const { return descriptor; }
    inline uint16_t getPort() const { return port; }
  private:
    Worker worker;
    uint16_t port;
    std::string ip;
    int32_t descriptor;

  };
}

#endif // COURSEWORK_SERVER_H
