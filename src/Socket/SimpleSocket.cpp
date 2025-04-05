#include "SimpleSocket.hpp"

namespace hde {
    SimpleSocket::SimpleSocket(int domain, int type, int protocol, int port, u_long interface) {
        memset(&address, 0, sizeof(address));
        address.sin_family = domain;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = htonl(interface);
    
        sock_fd = socket(domain, type, protocol);
        test_connection(sock_fd);                                           // Test socket creation
    
        // Let derived classes implement bind()/connect()
        connection_status = establish_socket_operation(sock_fd, address);
        test_connection(connection_status);                                 // Test bind/connect
    }

    void SimpleSocket::test_connection(int result) const {
        if (result < 0) {
            perror("Socket operation failed");
            throw std::runtime_error("Socket error");
        }
    }

    int SimpleSocket::get_socket() const {
        return sock_fd;
    }

    int SimpleSocket::get_connection_status() const {
        return connection_status;
    }

    const sockaddr_in& SimpleSocket::get_address() const {
        return address;
    }
}