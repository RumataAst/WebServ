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


// to check 
std::string Server::receiveMessage(int socket_fd) {
    char buffer[1024];
    int n = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);  // Leave space for '\0'

    // I need properly differentiate between n = 0 when client closed connection and error
    if (n <= 0) {
        return "";
    }

    buffer[n] = '\0';
    std::string received(buffer);
    // trim whitespace from the end
    received.erase(std::remove_if(received.begin(), received.end(), ::isspace), received.end());
    return received;
}

bool Server::sendMessage(int socket_fd, const std::string &message) {
    int bytes_sent = send(socket_fd, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Error sending message to client: " << strerror(errno) << std::endl;
        return false;
    }
    // the following check is needed if not the full message was sent - meaning bytes_sent != message.size() then i need to continue from the difference and send remaining message
    // additionally i should also check probably before sending a message if this particular socket is ready to accept....
    //  The questions is what do i do if it's not ready? Coz my program will probably stopped all together if i just wait in the loop for that 
    // i need to look more into poll() and more specifically POLLOUT	Alert me when I can send() data to this socket without blocking.
    return true;
}
