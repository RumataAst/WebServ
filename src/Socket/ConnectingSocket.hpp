#ifndef CONNECTING_SOCKET_HPP
#define CONNECTING_SOCKET_HPP

#include "SimpleSocket.hpp"

namespace hde {
    class ConnectingSocket : public SimpleSocket {
    public:
        ConnectingSocket(int domain, int type, int protocol, int port, u_long interface);
        int establish_socket_operation(int &sock_fd, const sockaddr_in &address) override;
    };
}
#endif