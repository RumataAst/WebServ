#include "Socket.hpp"

// COnstructors
Socket::Socket(const std::string& user_port) {
    int port = getValidPort(user_port);
    sock_fd = -1;
    // cleaning address structure before use
    std::memset(&address, 0, sizeof(address));
    // by default IP 4
    address.sin_family = DOMAIN;
    // Converting from host to network order of bytes
    address.sin_port = htons(port);             // Here is port taken from user
    address.sin_addr.s_addr = htonl(INTERFACE);

    sock_fd = socket(DOMAIN, TYPE_CONNECTION, PROTOCOL);
    test_connection(sock_fd, "Creating Socket");
}

// Commented for now. I think we will take port from user
// Socket::Socket(int domain, int type, int protocol, int port, u_long interface) {
//     sock_fd = -1;
//     // cleaning address structure before use
//     std::memset(&address, 0, sizeof(address));
//     address.sin_family = domain;
//     // Converting from host to network order of bytes
//     address.sin_port = htons(port);
//     address.sin_addr.s_addr = htonl(interface);
// 
//     sock_fd = socket(domain, type, protocol);
//     test_connection(sock_fd, "Creating Socket");
// }

// Getters
int Socket::get_socket() const {
    return sock_fd;
}

const sockaddr_in &Socket::get_address() const {
    return address;
}

// Socket operations
void Socket::bindSocket() {
    int result;

    int opt = 1; //enable bind to this socket to avoid "Address is already in use"
    result = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    test_connection(result, "setsockopt");

    result = bind(sock_fd, (struct sockaddr *)&address, sizeof(address));
    test_connection(result, "Binding socket");
}

// I can add listening_status as bool to identify that server is currently listening if needed
void Socket::listenSocket() {
    int result = listen(sock_fd, BACKLOG_QUEUE);
    test_connection(result, "Listening socket");
}

int Socket::acceptSocket() {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
    test_connection(client_fd, "Accepting socket");

    int result = fcntl(client_fd, F_SETFL, O_NONBLOCK);
    test_connection(result, "Setting socket as nonblocking");
    return client_fd;
}

// throwing error if the socket is less than 0
void    Socket::test_connection(int return_value,const std::string &phase) const {
    if (return_value < 0) {
        throw std::runtime_error("failed on the stage " + phase);
    }
}

// Checks if the port from user is valid, if yes then converts to int, no then throws error
int Socket::getValidPort(const std::string& user_port) {
    for (size_t i = 0; i < user_port.size(); ++i) {
        if (!std::isdigit(user_port[i])) {
            throw std::invalid_argument("Port must contain only digits.");
        }
    }

    // Use stringstream to convert to int
    std::istringstream iss(user_port);
    int port;
    iss >> port;

    // Check conversion success and port range
    if (iss.fail() || !iss.eof() || port < 1 || port > 65535) {
        throw std::invalid_argument("Invalid port number: must be a number between 1 and 65535.");
    }

    return port;
}


// Destructor
// Closing of the sockets will be on the Server? I might change it
Socket::~Socket() {
    if (sock_fd >= 0)
        close(sock_fd);
}
