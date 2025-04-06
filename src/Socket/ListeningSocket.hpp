#ifndef LISTENING_SOCKET_HPP
#define LISTENING_SOCKET_HPP

#include "BindingSocket.hpp"

namespace net {
    class ListeningSocket : public BindingSocket {
    private:
        int backlog; //Max pending connections
    public:
        ListeningSocket(int domain, int type, int protocol, int port, u_long interface, int backlog);
        void    start_listening();
        int     accept_connection(struct sockaddr_in &client_addr);
    };
}

#endif