#ifndef WEBSERV_HTTP_HPP
#define WEBSERV_HTTP_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h> 

namespace http {
    class TcpServer {
        public:
            TcpServer();
            ~TcpServer();
        
        private:
            std::string m_ip_address;
            long        m_incomingMessage;
            int         m_socket;
            int         m_port;
            int         m_new_socket;



            int     startServer();
            void    closeServer();

            // to prevent from being copied or assigned
            TcpServer &operator=(TcpServer &source);
            TcpServer(TcpServer &copy);

    };
} // namespace http

#endif