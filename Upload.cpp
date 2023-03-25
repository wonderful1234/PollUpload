// #define _WIN32_WINNT 0x0A00
// #include <iostream>
// #include <winsock2.h>
// #include <vector>
// #define poll(fds, nfds, timeout) WSAPoll(fds, nfds, timeout)
// using std::vector;
#include "TcpServer.h"
// #include "EventLoop.h"
// #include "Acceptor.h"
int main()
{
    // auto  main_reactor_=std::make_unique<EventLoop>();
    // auto acceptor_ = std::make_unique<Acceptor>(main_reactor_.get());
    // main_reactor_->loop();
     TcpServer *server = new TcpServer();
     server->start();

//    auto  main_reactor_=std::make_unique<EventLoop>();
//    auto acceptor_ = std::make_unique<Acceptor>(main_reactor_.get());
//    main_reactor_->loop();

    // WSADATA wsaData;
    // WSAStartup( MAKEWORD(2, 2), &wsaData);

    // //创建套接字
    // SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // //绑定套接字
    // struct sockaddr_in sockAddr;
    // memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    // sockAddr.sin_family = PF_INET;  //使用IPv4地址
    // sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    // sockAddr.sin_port = htons(1234);  //端口
    // bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    // //进入监听状态
    // listen(servSock, SOMAXCONN);
    // vector<struct pollfd> fds;
    // fds.push_back({servSock,POLLIN});
    // while (true)
    // {
    //    int ret=poll(&fds[0], fds.size(), -1);
    // }
    return 0;
    







}