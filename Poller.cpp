#include "Poller.h"

Poller::Poller()
{

}

Poller::~Poller()
{
   

}

vector<SOCKET> Poller::pollWait(int timeout)
{
    vector<SOCKET> sokets;
    auto ret=poll(&m_fds_[0],m_fds_.size(),timeout);
        if(ret <= 0)
        {
            return sokets;
        }
        for(auto & item:m_fds_)
        {
            if(item.revents & POLLIN)
            {
                sokets.push_back(item.fd);
                ret--;
                if(ret==0)
                {
                    break;
                }
            }
        }
        return sokets;
}

void Poller::updateFds(SOCKET fd)
{
    m_fds_.push_back({fd,POLLIN,0});
   
}