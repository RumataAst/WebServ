#ifndef BINDING_SOCKET_HPP
#define BINDING_SOCKET_HPP

#include "SimpleSocket.hpp"

namespace hde {
    class BindingSocket : public SimpleSocket {
    public:
        BindingSocket(int domain, int type, int protocol, int port, u_long interface);
        int establish_socket_operation(int &sock_fd, const sockaddr_in &address) override;
    };
}

#endif