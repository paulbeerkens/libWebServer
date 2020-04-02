#include <iostream>
#include "WebServer.h"
#include <assert.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
//#include <sstream>

std::string webserver::WebServer::version() const {
    //return std::to_string (LIBWEBSERVERVERSION);
    return LIBWEBSERVERVERSION;
}

void webserver::WebServer::registerURL(const std::string &url, webserver::WebServer::WebServerCB &cb) {
    bool inserted;
    std::tie (std::ignore, inserted)=registeredURLs_.emplace (url, cb);
    if (!inserted) {
        log ("Url "+url+" was already registered");
    };
}

void webserver::WebServer::log(std::string_view s) {
    std::cout<<s<<std::endl;
}

bool webserver::WebServer::start(std::int32_t port) {
    assert (port_==-1&&"Do not call start more than once.");
    port_=port;

    socket_=::socket (AF_INET, SOCK_STREAM, 0);
    if (socket_==-1) {
        log ("WebServer::start failed to create socket with error code "+std::to_string(errno)+" ("+strerror (errno)+")");
        return false;
    }

    struct sockaddr_in sockAddr;
    bzero (&sockAddr, sizeof (sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    sockAddr.sin_port = htons (port_);

    auto result=::bind (socket_, reinterpret_cast<const struct sockaddr*>(&sockAddr),sizeof (sockAddr));
    if (result!=0) {
        log ("WebServer::start failed to bind socket on port "+std::to_string (port_)+" with error code "+std::to_string(errno)+" ("+strerror (errno)+")");
        return false;
    }


    return true;
}
