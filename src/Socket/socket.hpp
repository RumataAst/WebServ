#include SOCKET_HPP
#define SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h> // for socket function
#include <netinet/in.h> // for address struct

namespace hde {
    class SimpleSocket{
        public:
        /* Default constructor requires from user domain, type and protocol more info in socket function
        domain specifies the communication domain in which a socket to be created. 
        type - type of the socket. SOCK_SREAM  SOCK_DGRAM and SOCK SEQPACKET can be used 
        protocol - for 0 it's default protocol
        port for Network
        interface on which socket is running
        */
            SimpleSocket(int domain, int type, int protocol, int port, u_long interface);
            virtual void create_network_connection(int sock_return,struct sockaddr_in address) = 0;
        private:
            int     sock_return, connection;
            struct  sockaddr_in_address;
    };
}

#endif