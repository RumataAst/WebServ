#include <iostream>
#include <thread>           // server and client
#include <chrono>           // Sleep for client
#include <unistd.h>
#include "../net.hpp"



void server_thread() {
    net::ListeningSocket listen_socket(AF_INET, SOCK_STREAM, 0, 12345, INADDR_ANY, 5);

    struct sockaddr_in client_addr;
    int client_fd = listen_socket.accept_connection(client_addr);
    std::cout << "Server accepted connection from client\n";

    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received > 0) {
            std::cout << "Server received: " << buffer << std::endl;
        } else if (bytes_received == 0) {
            std::cout << "Client disconnected\n";
            break;
        } else {
            std::cerr << "recv() error\n";
            break;
        }
    }

    close(client_fd);
}

int main() {
    try {
        std::thread server(server_thread);
        server.join();
        std::cout << "End of test\n";
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
