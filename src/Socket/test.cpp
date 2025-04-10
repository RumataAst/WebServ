#include <iostream>
#include <thread>           // server and client
#include <chrono>           // Sleep for client
#include <unistd.h>
#include "../net.hpp"


void server_thread() {
    net::BindingSocket bind_socket(AF_INET, SOCK_STREAM, 0, 12344, INADDR_ANY);
    net::ListeningSocket listen_socket(AF_INET, SOCK_STREAM, 0, 12345, INADDR_ANY, 5);

    struct sockaddr_in client_addr;
    int client_fd = listen_socket.accept_connection(client_addr);
    std::cout << "Server accepted connection from client\n";
    close(client_fd);
}

void client_thread() {
    // Give server a moment to set up
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    net::ConnectingSocket connect_socket(AF_INET, SOCK_STREAM, 0, 12345, INADDR_LOOPBACK);
    std::cout << "Client connected to server\n";
}

int main() {
    try {
        std::thread server(server_thread);
        std::thread client(client_thread);

        server.join();
        client.join();

        std::cout << "End of test\n";
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}