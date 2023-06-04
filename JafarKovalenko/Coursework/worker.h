#ifndef COURSEWORK_WORKER_H
#define COURSEWORK_WORKER_H

#include <cstdint>
#include <sys/epoll.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>


namespace Coursework {
  const uint16_t kMaxEvents{32};

  class Worker {
  public:
    explicit Worker();
    ~Worker();
    void setServerEvent(int32_t serverfd);
    void addToEpoll(int32_t descriptor) const;
    int16_t waitForEvents();
    void eventsHandling(int16_t numOfEvents);
    static void setClientNonblock(int32_t clientfd);
  private:
    int32_t epollfd;
    epoll_event serverEvent;
    std::vector<epoll_event> events;
    std::unordered_map<int32_t, std::string> clients;
  };

  enum WorkerError{};
}

#endif //COURSEWORK_WORKER_H
