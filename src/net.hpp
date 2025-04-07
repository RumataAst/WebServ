#ifndef NET_HPP
#define NET_HPP

#include "Socket/ConnectingSocket.hpp"
#include "Socket/ListeningSocket.hpp"

/**
 * Simple and Binding Sockets are parent for Listening 
 * so including ListeningSocket.hpp should be enough
 * but i will let it be for now
 */
#include "Socket/BindingSocket.hpp"
#include "Socket/SimpleSocket.hpp"

#endif