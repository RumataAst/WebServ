#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream> 
#include "../net.hpp"


namespace net {
    class Server {
    private:
        
    public:
        Server(int domain, int type, int protocol, int port, u_long interface, int backlog);
    }
}

#endif