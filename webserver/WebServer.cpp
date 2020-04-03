#include <iostream>
#include "WebServer.h"
#include <assert.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <future>
#include <unistd.h>
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
        port_=-1; //reset so that we could call start again possibly with a different port
        return false;
    }

    int enable = 1;
    if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        log ("setsockopt(SO_REUSEADDR) failed");
    }

    struct sockaddr_in sockAddr;
    bzero (&sockAddr, sizeof (sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    sockAddr.sin_port = htons (port_);

    auto result=::bind (socket_, reinterpret_cast<const struct sockaddr*>(&sockAddr),sizeof (sockAddr));
    if (result!=0) {
        log ("WebServer::start failed to bind socket on port "+std::to_string (port_)+" with error code "+std::to_string(errno)+" ("+strerror (errno)+")");
        port_=-1; //reset so that we could call start again possibly with a different port
        return false;
    }

    result = ::listen (socket_, SOMAXCONN); //allow the maximum number of connections to be queued up waiting for an accept call
    if (result!=0) {
        log ("WebServer::start failed to listen socket on port "+std::to_string (port_)+" with error code "+std::to_string(errno)+" ("+strerror (errno)+")");
        port_=-1; //reset so that we could call start again possibly with a different port
        return false;
    }

    assert (threadPtr_==nullptr);

    std::promise <void> threadStartedPromise_;
    threadPtr_=std::make_unique <std::thread> ([this, &threadStartedPromise_] () {
        threadStartedPromise_.set_value();
        this->doWork ();});

    threadStartedPromise_.get_future().wait(); //wait till thread has been started;

    return true;
}

void webserver::WebServer::doWork() {
    log ("Webserver listening to port "+std::to_string (port_));

    while (!requestedToTerminate_.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        struct sockaddr_in clientAddr;
        socklen_t len;

        auto newSocket=::accept (socket_, reinterpret_cast<struct sockaddr*>(&clientAddr), &len);

        std::cout<<"A Connection"<<std::endl;
        ::close (newSocket);
    }
}

bool webserver::WebServer::stop() {
    requestedToTerminate_.store(true);

    if (threadPtr_ && threadPtr_->joinable()) {
        threadPtr_->join ();
    }
    if (socket_!=-1) {
        ::close (socket_);
        socket_=-1;
    }
    return false;
}
