#include "ConnectingSocket.hpp"


namespace hde {
    ConnectingSocket::ConnectingSocket(int domain, int type, int protocol, int port, u_long interface) 
        : SimpleSocket(domain, type, protocol, port, interface) {}

    // implementation of pure virtual function that is inhereted from parent. In ConnectingSocket connect is used.
    int ConnectingSocket::establish_socket_operation(int &sock_fd, const sockaddr_in &address) {
        return connect(sock_fd, (struct sockaddr *)&address, sizeof(address));
    }
}