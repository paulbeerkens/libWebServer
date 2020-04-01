#include "WebServer.h"
//#include <sstream>

std::string WebServer::version() const {
    //return std::to_string (LIBWEBSERVERVERSION);
    return LIBWEBSERVERVERSION;
}
