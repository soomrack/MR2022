#include "worker.h"
#include <iostream>
#include <sstream>
#include <cstring>

#include <chrono>
#include <ctime>
#include <iomanip>

#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <csignal>


Coursework::Worker::Worker() : serverEvent{}
{
  try
  {
    epollfd = epoll_create1(0);
    if (epollfd < 0)
      throw std::string{"Epoll creation failed.\n"};
  }
  catch (std::string& exception)
  {
    std::cerr << exception;
    exit(-1);
  }

  serverEvent.events = EPOLLIN;
  events.resize(kMaxEvents);
}

Coursework::Worker::~Worker()
{
  for (auto& client : clients)
    close(client.first);
}

void Coursework::Worker::setServerEvent(int32_t serverfd)
{
  serverEvent.data.fd = serverfd;
  addToEpoll(serverfd);
}

void Coursework::Worker::addToEpoll(int32_t descriptor) const
{
  epoll_event event{};
  event.data.fd = descriptor;
  event.events = EPOLLIN;
  try
  {
    bool isAddToEpollFailed = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor, &event);
    if (isAddToEpollFailed) throw std::string{"Addition to epoll error.\n"};
  }
  catch (std::string& exception)
  {
    std::cerr << exception;
    std::cout << errno << "\n";
  }
}

int16_t Coursework::Worker::waitForEvents()
{
  try
  {
    auto numOfEvents = static_cast<int16_t>(epoll_wait(epollfd, &events[0],
                                                       kMaxEvents, -1));
    if (numOfEvents < 0) throw std::string{"Waiting for events error.\n"};
    return numOfEvents;
  }
  catch (std::string& exception)
  {
    std::cerr << exception;
    return {};
  }
}

void Coursework::Worker::eventsHandling(int16_t numOfEvents)
{
  for (int16_t i = 0; i < numOfEvents; i++)
  {
    epoll_event& e = events[i];

    if (e.data.fd == serverEvent.data.fd)  // branch for server event handling
    {
      sockaddr_in clientAddress{};
      socklen_t sizeOfClientAddress = sizeof(clientAddress);

      int32_t clientfd = accept(serverEvent.data.fd,
                                reinterpret_cast<sockaddr *>(&clientAddress), &sizeOfClientAddress);

      setClientNonblock(clientfd);

      addToEpoll(clientfd);

      std::stringstream str;
      str << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port);
      clients[clientfd] = str.str();
      std::cout << clients[clientfd] << " connected.\n";
    }
    else
    {
      static const uint16_t length{1024};
      static std::vector<char> buffer(length, 0);

      auto result = static_cast<int32_t>(recv(e.data.fd, buffer.data(), length, MSG_NOSIGNAL));

      if (result == 0 && errno != EAGAIN)
      {
        close(e.data.fd);
        std::stringstream str;
        str << clients[e.data.fd] << " disconnected.\n";
        std::cout << str.str();
        clients.erase(e.data.fd);
      }
      else if (result > 0)
      {
        std::stringstream str;
        buffer[4] = '\0';
        if (strcmp(buffer.data(), "time") == 0)
        {
          const std::time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
          str << std::put_time(std::localtime(&t_c), "%F %T\n");
          std::cout << "Sent time to client " << clients[e.data.fd] << "\n";
        }
        else
        {
          std::cout << "Client " << clients[e.data.fd] << " sent wrong request.\n";
          str << "Wrong request. Try writing \"time\" again.\n";
        }
        send(e.data.fd, str.str().data(), str.str().length(), MSG_NOSIGNAL);
      }
    }
  }
}

void Coursework::Worker::setClientNonblock(int32_t clientfd)
{
    int16_t flags;
#if defined(O_NONBLOCK)
  flags = static_cast<int16_t>(fcntl(clientfd, F_GETFL, 0));
  if(flags == -1)
    flags = 0;
  fcntl(clientfd, F_SETFL, flags | O_NONBLOCK);
#else
  flags = 1;
  ioctl(clientfd, FIONBIO, &flags);
#endif
}
