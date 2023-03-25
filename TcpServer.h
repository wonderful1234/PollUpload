#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Socket.h"
class EventLoop;
class Acceptor;
class Connection;
class ThreadPool;
class TcpServer
{
private:
    std::unique_ptr<EventLoop> m_main_reactor_;
    std::unique_ptr<Acceptor> m_acceptor_;
    std::unordered_map<int, std::unique_ptr<Connection>> m_connections_;
    std::vector<std::unique_ptr<EventLoop>> m_sub_reactors_;
    std::unique_ptr<ThreadPool> m_thread_pool_;

  
public:
    TcpServer();
    ~TcpServer();
    void newConnection(SOCKET fd);
    void deleteConnection(SOCKET fd);
    void readHandle(SOCKET fd);
    void start();
};


