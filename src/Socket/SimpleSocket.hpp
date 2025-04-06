#ifndef SIMPLE_SOCKET_HPP
#define SIMPLE_SOCKET_HPP

#include <iostream>
#include <cstring>      // memset
#include <stdexcept>    // std::runtime_error
#include <sys/socket.h> // socket, bind, connect
#include <netinet/in.h> // sockaddr_in

namespace net {
    class SimpleSocket {
    private:
        int                 sock_fd;            // Socket file descriptor
        int                 connection_status;  // Connection status (bind/connect result)
        struct sockaddr_in  address;            // Socket address structure

    public:
        /**
         * @brief Constructs a new SimpleSocket
         * @param domain   Communication domain (AF_INET, AF_INET6, etc.)
         * @param type     Socket type (SOCK_STREAM, SOCK_DGRAM)
         * @param protocol Protocol (0 for default)
         * @param port     Port number in host byte order
         * @param interface Network interface (INADDR_ANY for all interfaces)
         * @throws std::runtime_error if socket creation fails
         */
        SimpleSocket(int domain, int type, int protocol, int port, u_long interface);
        
        virtual ~SimpleSocket() = default; // Virtual destructor for polymorphism

        // Prevent copying
        SimpleSocket(const SimpleSocket&) = delete;
        SimpleSocket& operator=(const SimpleSocket&) = delete;

        /**
         * @brief Tests if a socket operation succeeded
         * @param result Result of the operation (negative means failure)
         * @throws std::runtime_error if result < 0
         */
        void test_connection(int result) const;

        // Getters
        int get_socket() const;
        int get_connection_status() const;
        const sockaddr_in& get_address() const;

        /**
         * @brief Pure virtual function for specific operations (bind/connect), inhereted by other sockets
         * @param sock_fd Socket file descriptor
         * @param address Socket address structure
         * @return int Result of the operation (must be non-negative on success)
         */
        virtual int establish_socket_operation(int &sock_fd, const sockaddr_in &address) = 0;

        // Creating new function in order to avoid calling pure virtual function in constructor
        void    setup(void);    
    };
}

#endif