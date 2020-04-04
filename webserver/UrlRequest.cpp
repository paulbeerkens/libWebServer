#include "UrlRequest.h"
#include <iostream>

webserver::UrlRequest::UrlRequest(const std::string& remoteIP)
:remoteIP_ (remoteIP) {

}

bool webserver::UrlRequest::processRequestLine(const std::string &line) {
    return false;
}
