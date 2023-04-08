#pragma once
#define _WIN32_WINNT 0x0A00
#include <winsock2.h>
#include <tuple>
class Socket
{
private:
   SOCKET m_socket_;

  
public:
    Socket();
    ~Socket();
    bool creat();
    bool bind(const char * ip,u_short port);
    bool listen();
    bool accept(SOCKET & clnt_fd);
    bool connect(const char *ip, u_short port);
    SOCKET fd();
    void set_fd(SOCKET fd);
    std::tuple< std::string , u_short > get_addr() const;
};
