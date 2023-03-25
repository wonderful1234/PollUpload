#pragma once
#include "Socket.h"
#include <functional>
#include <memory>
class EventLoop;
class Connection
{
private:
    std::unique_ptr<Socket> m_socket_;
    std::function<void(int)> m_delete_connectioin_;
public:
    Connection(SOCKET fd, EventLoop *loop);
    ~Connection();
    void read();
    void set_delete_connection(std::function<void(int)> const &fn);
};


