//
// Created by pbeerken on 8/21/17.
//

#ifndef LIBWEBSERVER_WEBSERVER_H
#define LIBWEBSERVER_WEBSERVER_H

#include <string>
#include <unordered_map>

class WebServerCB
{
public:
    virtual bool onURLRequest(std::ostream &os)=0;
};

class WebServer
{
public:
    static WebServer &get()
    {
        static WebServer instance;
        return instance;
    }

    void registerURL(const std::string &url, WebServerCB *cb);

    void onUnrecognizedURL(std::ostream &os);

    std::string version () const;
protected:
    WebServer(WebServer const &) = delete;             // Copy construct
    WebServer(WebServer &&) = delete;                  // Move construct
    WebServer &operator=(WebServer const &) = delete;  // Copy assign
    WebServer &operator=(WebServer &&) = delete;      // Move assign

    WebServer()
    {

    }

    std::unordered_map<std::string, WebServerCB *> registeredURLs_;


};


#endif //LIBWEBSERVER_WEBSERVER_H
