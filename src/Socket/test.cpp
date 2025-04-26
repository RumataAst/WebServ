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

    char buffer[1024] = {};
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "Server received: " << buffer << std::endl;

        const char *reply = "Hello from server";
        send(client_fd, reply, strlen(reply), 0);
    }

    close(client_fd);
}

void client_thread() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    net::ConnectingSocket connect_socket(AF_INET, SOCK_STREAM, 0, 12345, INADDR_LOOPBACK);

    int sockfd = connect_socket.get_socket();

    const char *msg = "Hello from client";
    send(sockfd, msg, strlen(msg), 0);
    std::cout << "Client sent message\n";

    char buffer[1024] = {};
    int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "Client received: " << buffer << std::endl;
    }

    close(sockfd);
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
