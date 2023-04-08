#include "Socket.h"

Socket::Socket() : m_socket_(-1) {}
Socket::~Socket()
{
    if(m_socket_!=-1)
    {
        closesocket(m_socket_);
    }
}
bool Socket::creat()
{
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);
    m_socket_=socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket_==-1)
    {
        return false;
    }
    return true;
}

bool Socket::bind(const char * ip,u_short port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    if(::bind(m_socket_,(struct sockaddr *)&addr, sizeof(addr))==-1)
    {
        return false;
    }
    return true;
 

}

bool Socket::listen()
{
    if(::listen(m_socket_,SOMAXCONN)==-1)
    {
        return false;
    }
    return true;
}

bool Socket::accept(SOCKET & clnt_fd)
{
    clnt_fd=::accept(m_socket_,nullptr,nullptr);
    if(clnt_fd==-1)
    {
        return false;
    }
    return true;
}

bool Socket:: connect(const char *ip, u_short port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    if(::connect(m_socket_,(struct sockaddr *)&addr, sizeof(addr))==-1)
    {
        return false;
    }
    return true;
 
  
}
SOCKET Socket:: fd()
{
    return m_socket_;
}

void Socket:: set_fd(SOCKET fd)
{
    m_socket_=fd;
}

std::tuple< std::string , u_short > Socket:: get_addr() const
{
    std::tuple<std::string, u_short > data("", 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    int len = sizeof(addr);
    if(getsockname(m_socket_, (struct sockaddr *)&addr, &len)==-1)
    {
        return data;
    }
    std::get<0>(data) = inet_ntoa(addr.sin_addr);
    std::get<1>(data)=htons(addr.sin_port);
    return data;
    
    
}