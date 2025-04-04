#include "socket.hpp"


namespace hde {
    SimpleSocket::SimpleSocket(int domain, int type, int protocol, int port, u_long interface) {
        // Defining address structure
        address.sin_family = domain;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = htonl(interface);
        // Creating an unbound socket in a communication domain. Sock_return is a file descriptor that will be used by cliend and server
        sock_return = socket(domain, type, protocol);
        test_connection(sock_return);
        
        // Connection is created based on class implementing it. Either bind or connect
        connection = create_network_connection(sock_return, address);
        test_connection(connection);
    }

    void SimpleSocket::test_connection (int item_to_test) {
        if (item_to_test < 0) {
            std::cerr << "Failed to connect\n";
            exit(EXIT_FAILURE);
        }
    }

    int SimpleSocket::get_socket() const {
        return sock_return;
    }

    int SimpleSocket::get_connection() const {
        return connection;
    }

    struct  sockaddr_in SimpleSocket::get_address() const {
        return address;
    }

}