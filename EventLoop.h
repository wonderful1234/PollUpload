#pragma once
#include "Socket.h"
#include <memory>
#include <functional>
class Poller;
class EventLoop
{
private:
    std::unique_ptr<Poller> m_poller_;
    std::function<void()> m_connect_callback_;
    std::function<void(int)> m_read_callback_;
    std::unique_ptr<Socket> m_fake_socket_;
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateFds(SOCKET fd);
    void set_connect_callback(std::function<void()> const &callback);
    void set_read_callback(std::function<void(int)> const &callback);


};
