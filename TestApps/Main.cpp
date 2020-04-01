#include <webserver/WebServer.h>
#include <iostream>


int main (int argc, char** args) {
    std::cout<<WebServer::get ().version ()<<std::endl;
    return 0;
}
