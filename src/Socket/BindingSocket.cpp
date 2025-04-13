#include "BindingSocket.hpp"


namespace net {
    BindingSocket::BindingSocket(int domain, int type, int protocol, int port, u_long interface) 
        : SimpleSocket(domain, type, protocol, port, interface) {
            setup();
        }

    // implementation of pure virtual function that is inhereted from parent.
    int BindingSocket::establish_socket_operation(int &sock_fd, const sockaddr_in &address) {
        return bind(sock_fd, (struct sockaddr *)&address, sizeof(address));
    }n
    
}