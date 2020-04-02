#ifndef LIBWEBSERVER_URLREQUEST_H
#define LIBWEBSERVER_URLREQUEST_H

#include <string_view>
#include <unordered_map>

namespace webserver {

class UrlRequest {
public:
    explicit UrlRequest (std::string_view sv);
protected:
    std::unordered_map <std::string, std::string> params_;
};

}

#endif //LIBWEBSERVER_URLREQUEST_H
