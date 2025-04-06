#include "Socket/ConnectingSocket.hpp"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>  // for strlen
#include <fcntl.h>  // for fcntl

int main() {
    try {
        // Create client socket and connect to localhost:12345
        net::ConnectingSocket client(AF_INET, SOCK_STREAM, 0, 12345, inet_addr("127.0.0.1"));
        std::cout << "Connected to server!" << std::endl;

        // Make the socket non-blocking
        int client_fd = client.get_socket();
        int flags = fcntl(client_fd, F_GETFL, 0);
        if (flags == -1) {
            perror("fcntl failed");
            return 1;
        }
        fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);  // Set non-blocking mode
        std::cout << "Socket is now non-blocking" << std::endl;

        // Send message
        const char *message = "Hello from client!";
        ssize_t bytes_sent = write(client_fd, message, strlen(message));
        if (bytes_sent < 0) {
            perror("Write failed");
            return 1;
        }
        std::cout << "Sent " << bytes_sent << " bytes to server" << std::endl;

        // Read response
        char buffer[1024];
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer)-1);
        if (bytes_read < 0) {
            perror("Read failed");
            return 1;
        } else if (bytes_read == 0) {
            std::cout << "Server closed the connection" << std::endl;
        } else {
            buffer[bytes_read] = '\0';
            std::cout << "Server response: " << buffer << std::endl;
        }

        // Close socket properly
        close(client_fd);
    } catch (const std::exception &e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
