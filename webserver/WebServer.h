#ifndef LIBWEBSERVER_WEBSERVER_H
#define LIBWEBSERVER_WEBSERVER_H

#include <string>
#include <unordered_map>
#include "UrlRequest.h"
#include <functional>
#include <thread>
#include <atomic>

namespace webserver {

class WebServer {
public:
    typedef std::function <bool (const UrlRequest&, std::ostream&)> WebServerCB;

    static WebServer &get() {
        static WebServer instance;
        return instance;
    }

    void registerURL(const std::string &url, const WebServerCB& cb);

    void onUnrecognizedURL(std::ostream &os);

    std::string version() const;

    void log (std::string_view s);

    bool start (std::int32_t port);

    bool stop ();

    void cleanupForUnitTest () {
        stop ();
        threadPtr_=nullptr;
        port_=-1;
    }
protected:
    WebServer(WebServer const &) = delete;             // Copy construct
    WebServer(WebServer &&) = delete;                  // Move construct
    WebServer &operator=(WebServer const &) = delete;  // Copy assign
    WebServer &operator=(WebServer &&) = delete;      // Move assign
    WebServer ()
    :indexPageCB_ { [this] (const UrlRequest& urlRequest, std::ostream& os)->bool {generateDefaultIndexPage (urlRequest,os); return true;}} //set the callback to generateDefaultIndexPage
    {

    }

    ~WebServer () {stop ();}

    void doWork (); //the thread that does the actual work for this library
                    //in the future can be changed to a thread pool or
                    //even an external thread.

    void processRequest (const UrlRequest& urlRequest, std::ostream& os) const;

    std::unordered_map<std::string, WebServerCB> registeredURLs_;
    WebServerCB indexPageCB_; //this is called when the requested url was not found
    bool generateDefaultIndexPage (const UrlRequest&, std::ostream&) const;

    std::int32_t port_ {-1};
    int socket_ {-1};

    std::unique_ptr <std::thread> threadPtr_;
    std::atomic <bool> requestedToTerminate_;

    std::optional <UrlRequest> readRequest (int socket, const std::string& remoteIP);
};

}

#endif //LIBWEBSERVER_WEBSERVER_H
