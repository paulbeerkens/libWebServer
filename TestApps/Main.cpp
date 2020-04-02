#include <webserver/WebServer.h>
#include <iostream>


int main (int argc, char** args) {
    std::cout<<webserver::WebServer::get ().version ()<<std::endl;

    webserver::WebServer::get ().start (25000);
    return 0;
}
