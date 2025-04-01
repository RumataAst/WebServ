#include "socket.hpp"


namespace hde {
    SimpleSocket::SimpleSocket(domain, type, protocol, port, interface) {
        // Defining address structure
        address.sin_family = domain;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = htonl(interface);
        // Creating an unbound socket in a communication domain. Sock_return is a file descriptor that will be used by cliend and server
        sock_return = socket(domain, type, protocl);
        // Connection is created based on class implementing it. Either bind or connect
        connection = create_network_connection();
    }

}