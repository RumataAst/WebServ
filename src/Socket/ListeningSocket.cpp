#include "ListeningSocket.hpp"

namespace net {
    ListeningSocket::ListeningSocket(int domain, int type, int protocol, int port, u_long interface, int backlog)
    : BindingSocket(domain, type, protocol, port, interface), backlog(backlog) {
        start_listening();
}

    void ListeningSocket::start_listening() {
        std::cout << "[SERVER] Listening on fd " << get_socket() << std::endl;
        test_connection(listen(get_socket(), backlog));
    }

    int ListeningSocket::accept_connection(struct sockaddr_in &client_addr) {
        socklen_t addr_len = sizeof(client_addr);
        int client_fd = accept(get_socket(), (sockaddr*)&client_addr, &addr_len);
        test_connection(client_fd);
        return client_fd;
    }
}