#include "Socket/ListeningSocket.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>  // for strlen

int main() {
    try {
        // Create server that listens on port 12345
        net::ListeningSocket server(AF_INET, SOCK_STREAM, 0, 12345, INADDR_ANY, 5);
        std::cout << "Server listening on port 12345..." << std::endl;

        while (true) {
            // Accept incoming connection
            sockaddr_in client_addr;
            int client_fd = server.accept_connection(client_addr);
            std::cout << "New client connected!" << std::endl;

            // Read client message
            char buffer[1024];
            ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer)-1);
            if (bytes_read < 0) {
                perror("Read failed");
                close(client_fd);
                continue;
            } else if (bytes_read == 0) {
                std::cout << "Client disconnected" << std::endl;
                close(client_fd);
                continue;
            }

            buffer[bytes_read] = '\0';
            std::cout << "Received: " << buffer << std::endl;
            
            // Send response
            const char *response = "Message received!";
            ssize_t bytes_sent = write(client_fd, response, strlen(response));
            if (bytes_sent < 0) {
                perror("Write failed");
            }

            close(client_fd); // Close client socket
        }
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}