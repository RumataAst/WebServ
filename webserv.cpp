#include "webserv.hpp"

namespace http {

    TcpServer::TcpServer() {
        startServer();
    }

    TcpServer::~TcpServer() {
        closeServer();
    }

    int TcpServer::startServer() {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0) {
            std::cerr << "Cannot create a socket\n";
            return 1;
        }
        std::cout << "Socket is " << m_socket << std::endl;
        return 0;
    }

    void    TcpServer::closeServer() {
        close(m_socket);
        close(m_new_socket);
    }

}