#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdexcept>        // throw exception
#include <sys/socket.h>     // socket operations - bind, connect, listen
#include <netinet/in.h>     // sockaddr_in struct info
#include <cstring>          // std::memset
#include <string>           // convert from std::string c_str
#include <unistd.h>         // close()
#include <fcntl.h>          // fcntl()
#include <sstream>          // stream to convert port


// maybe in the future move this to separate file? 
#define DOMAIN          AF_INET             // using IP4; for IPv6 IF_INET6
#define TYPE_CONNECTION SOCK_STREAM         // for our purposes using TCP 
#define PROTOCOL        0                   // not specific
// #define PORT            12345            // port is taken from user
#define INTERFACE       INADDR_ANY          // to bind all networks interfaces
#define BACKLOG_QUEUE   5                   // how many connection waiting in the queue are allowed



/* Socket class 
 * This class will be part of the server class.
 * Main functions are:
 * Create socket for server with in constuctor
 * bind it to specific port and IP (using forced bind with setsockopt();
 * and start listening to it.
 * If connection is found then return new socket_fd
 *
 * Throwing errors if there is an error in any of the steps.
 */

class Socket {
private:
    int                 sock_fd;            // Socket file descriptor
    struct sockaddr_in  address;            // Socket address structure

    // Prevent copying
    Socket(const Socket &copy);
    Socket &operator =(const Socket &source);

public:
    /*
    * Constructors 
    * 1 for specific conditions from user if needed
    * other will take initialize based on the default values
    * TO-DO: Later i will correct constructor as we need to take port from user if I am not mistaken
    */

    // Not sure if needed
    // Socket(int domain, int type, int protocol, int port, u_long interface);
    Socket(const std::string& user_port);

    void    bindSocket();
    void    listenSocket();
    int     acceptSocket();
    void    setNonBlocking();

    // Testing purposes for client
    // void connectSocket();

    // Getters
    int                 get_socket() const;
    const sockaddr_in   &get_address() const;

    // Utils
    int getValidPort(const std::string& user_port);


    // Destructor
    ~Socket();

    //Error throw 
    void    test_connection(int return_value,const std::string &phaze) const;
};

#endif
