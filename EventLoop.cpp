#include "EventLoop.h"
#include "Poller.h"
EventLoop::EventLoop()
{
    m_poller_=std::make_unique<Poller>();
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
            if(fd==m_acceptor_->fd())
            {
                char buf[1024];
                memset(buf, 0, sizeof(buf));
                recv(m_acceptor_->fd(),buf,sizeof(buf),0);
            }
            else
            {
                 m_read_callback_(fd);
            }
           
        }

       }
       
    }
    
}

void EventLoop::updateFds(SOCKET fd)
{
    m_poller_->updateFds(fd);
    wakeup();
}

void EventLoop::set_connect_callback(std::function<void()> const &callback)
{
    m_connect_callback_ = std::move(callback);
}

 void EventLoop:: set_read_callback(std::function<void(int)> const &callback)
 {
    m_read_callback_=std::move(callback);
 }

 void EventLoop:: set_pair()
 {
    auto listener=std::make_unique<Socket>();
    listener->creat();
    listener->bind("127.0.0.1",0);
    listener->listen();
    m_connector_=std::make_unique<Socket>();
    m_connector_->creat();
    std::string ip = "";
	u_short port = 0;
	auto tp=listener->get_addr();
	std::tie(ip, port) = tp;
    m_connector_->connect(ip.c_str(),port);
    SOCKET clnt_fd=-1;
    listener->accept(clnt_fd);
    m_acceptor_=std::make_unique<Socket>();
    m_acceptor_->set_fd(clnt_fd);
    m_poller_->updateFds(m_acceptor_->fd());

 }

void EventLoop:: wakeup()
{
    if(m_connector_ && m_acceptor_)
    {
        const char * message="wake up";
        auto s=send(m_connector_->fd(),"wake up",strlen(message),0);
        if(s > 0)
        {
            
        }
    }

}
