#include "Connection.h"
#include "EventLoop.h"
Connection::Connection(SOCKET fd, EventLoop *loop)
{
    m_socket_ = std::make_unique<Socket>();
    m_socket_->set_fd(fd);
    loop->updateFds(fd);
}

Connection::~Connection()
{
}

 void Connection:: read()
 {
    auto sockfd=m_socket_->fd();
    char buf[1024];
    auto size=::recv(sockfd,buf,sizeof(buf),0);
    if(size <= 0)
    {
        m_delete_connectioin_(m_socket_->fd());
    }

 }

 void Connection::set_delete_connection(std::function<void(int)> const &fn)
 {
    m_delete_connectioin_=std::move(fn);

 }