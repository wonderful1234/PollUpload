#pragma once
#include <memory>
#include <functional>
class EventLoop;
class Socket;
class Acceptor
{
private:
   std::unique_ptr<Socket> m_socket_;
    std::function<void(int)> m_new_connection_callback_;
public:
    Acceptor(EventLoop * loop);
    ~Acceptor();
    void acceptConnection();
    void set_new_connection_callback(std::function<void(int)> const &callback);
};

