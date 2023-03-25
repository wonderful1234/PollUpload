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

SOCKET Socket:: fd()
{
    return m_socket_;
}

void Socket:: set_fd(SOCKET fd)
{
    m_socket_=fd;
}