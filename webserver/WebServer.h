#ifndef LIBWEBSERVER_WEBSERVER_H
#define LIBWEBSERVER_WEBSERVER_H

#include <string>
#include <unordered_map>
#include "UrlRequest.h"
#include <functional>

namespace webserver {

class WebServer {
public:
    typedef std::function <bool (const UrlRequest&, std::ostream&)> WebServerCB;

    static WebServer &get() {
        static WebServer instance;
        return instance;
    }

    void registerURL(const std::string &url, WebServerCB& cb);

    void onUnrecognizedURL(std::ostream &os);

    std::string version() const;

    void log (std::string_view s);

    bool start (std::int32_t port);

protected:
    WebServer(WebServer const &) = delete;             // Copy construct
    WebServer(WebServer &&) = delete;                  // Move construct
    WebServer &operator=(WebServer const &) = delete;  // Copy assign
    WebServer &operator=(WebServer &&) = delete;      // Move assign

    WebServer() {

    }

    std::unordered_map<std::string, WebServerCB> registeredURLs_;

    std::int32_t port_ {-1};
    int socket_ {-1};
};

}

#endif //LIBWEBSERVER_WEBSERVER_H
