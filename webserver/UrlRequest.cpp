#include "UrlRequest.h"
#include <iostream>

webserver::UrlRequest::UrlRequest(std::string_view sv) {
    for (auto c: sv) {
        std::cout<<c<<std::endl;
    }
}
