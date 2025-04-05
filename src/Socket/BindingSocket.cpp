#include "BindingSocket.hpp"


namespace hde {
    BindingSocket::BindingSocket(int domain, int type, int protocol, int port, u_long interface) 
        : SimpleSocket(domain, type, protocol, port, interface) {} // Base class does the work

    // implementation of pure virtual function that is inhereted from parent. In BindingSocket bind is used
    int BindingSocket::establish_socket_operation(int &sock_fd, const sockaddr_in &address) {
        return bind(sock_fd, (struct sockaddr *)&address, sizeof(address));
    }
}