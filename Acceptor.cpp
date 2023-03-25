#include "Acceptor.h"
#include "EventLoop.h"
#include "Socket.h"
Acceptor::Acceptor(EventLoop * loop)
{
    m_socket_=std::make_unique<Socket>();
    m_socket_->creat();
    m_socket_->bind("127.0.0.1",1234);
    m_socket_->listen();
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    loop->set_connect_callback(cb);
    loop->updateFds(m_socket_->fd());
}

Acceptor::~Acceptor()
{
}

 void Acceptor::acceptConnection()
 {
    SOCKET clnt_fd=-1;
    m_socket_->accept(clnt_fd);
    if(m_new_connection_callback_)
    {
        m_new_connection_callback_(clnt_fd);

    }
    
 }

 void Acceptor::set_new_connection_callback(std::function<void(int)> const &callback)
 {
    m_new_connection_callback_=std::move(callback);
 }