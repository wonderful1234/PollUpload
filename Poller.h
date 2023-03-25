#pragma once
#include "Socket.h"
#include <vector>
#define poll(fds, nfds, timeout) WSAPoll(fds, nfds, timeout)
using std::vector;
class Poller
{
private:
    vector<struct pollfd> m_fds_;
public:
    Poller();
    ~Poller();
    vector<SOCKET> pollWait(int timeout);
    void updateFds(SOCKET fd);
};

