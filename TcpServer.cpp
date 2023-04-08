#include "TcpServer.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"
TcpServer::TcpServer()
{
    m_main_reactor_ = std::make_unique<EventLoop>();
    m_acceptor_ = std::make_unique<Acceptor>(m_main_reactor_.get());
    std::function<void(int)> cb = std::bind(&TcpServer::newConnection, this, std::placeholders::_1);
    m_acceptor_->set_new_connection_callback(cb);

    u_int size=1;
    m_thread_pool_= std::make_unique<ThreadPool>(size);
    for(u_int i = 0; i < size; ++i)
    {
        std::unique_ptr<EventLoop> sub_reactor = std::make_unique<EventLoop>();
        std::function<void(int)> cb = std::bind(&TcpServer::readHandle, this, std::placeholders::_1);
        sub_reactor->set_read_callback(cb);
        sub_reactor->set_pair();
        m_sub_reactors_.push_back(std::move(sub_reactor));
    }
}

TcpServer::~TcpServer()
{
}

void TcpServer:: newConnection(SOCKET fd)
{
    uint64_t random = fd % m_sub_reactors_.size();
    std::unique_ptr<Connection> conn = std::make_unique<Connection>(fd, m_sub_reactors_[random].get());
    std::function<void(int)> cb = std::bind(&TcpServer::deleteConnection, this, std::placeholders::_1);
    conn->set_delete_connection(cb);
    m_connections_[fd] = std::move(conn);

}

void TcpServer:: deleteConnection(SOCKET fd)
{
    auto it = m_connections_.find(fd);
    if(it!=m_connections_.end())
    {
        m_connections_.erase(fd);
    }
}

void TcpServer:: readHandle(SOCKET fd)
{
    auto it = m_connections_.find(fd);
    if(it!=m_connections_.end())
    {
       it->second->read();
    }

}

void TcpServer::start()
  {
    for(size_t i=0;i < m_sub_reactors_.size();++i)
    {
         std::function<void()> sub_loop = std::bind(&EventLoop::loop, m_sub_reactors_[i].get());
         m_thread_pool_->Add(sub_loop);
    }
    m_main_reactor_->loop();
  }

  