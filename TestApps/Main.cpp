#include <webserver/WebServer.h>
#include <iostream>
#include <chrono>
#include <thread>


int main () {
    std::cout<<webserver::WebServer::get ().version ()<<std::endl;

    if (!webserver::WebServer::get ().start (25000)) {
        std::cout<<"Failed to start webserver."<<std::endl;
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::seconds (300));

    webserver::WebServer::get ().stop ();

    return 0;
}
