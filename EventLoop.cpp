#include "EventLoop.h"
#include "Poller.h"
EventLoop::EventLoop()
{
    m_poller_=std::make_unique<Poller>();
    m_fake_socket_=std::make_unique<Socket>();
    m_fake_socket_->creat();
    m_poller_->updateFds(m_fake_socket_->fd());
}

EventLoop::~EventLoop()
{

}

void EventLoop::loop()
{
    while (true)
    {
       auto sockets= m_poller_->pollWait(-1);
       if(sockets.empty())
       {
        continue;
       }
       if(m_connect_callback_)
       {
        m_connect_callback_();
       }
       else if(m_read_callback_)
       {
        for(auto fd : sockets)
        {
            m_read_callback_(fd);
        }

       }
       
    }
    
}

void EventLoop::updateFds(SOCKET fd)
{
    m_poller_->updateFds(fd);
    if(m_fake_socket_)
    {
        const char * message="wake up";
        send(m_fake_socket_->fd(),"wake up",strlen(message),0);
    }
}

void EventLoop::set_connect_callback(std::function<void()> const &callback)
{
    m_connect_callback_ = std::move(callback);
}

 void EventLoop:: set_read_callback(std::function<void(int)> const &callback)
 {
    m_read_callback_=std::move(callback);
 }
