#ifndef LIBWEBSERVER_URLREQUEST_H
#define LIBWEBSERVER_URLREQUEST_H

#include <string_view>
#include <unordered_map>

namespace webserver {

class UrlRequest {
public:
    explicit UrlRequest (const std::string& remoteIP);
    bool processRequestLine (const std::string& line);
protected:
    std::unordered_map <std::string, std::string> params_;
    std::string remoteIP_;
};

}

#endif //LIBWEBSERVER_URLREQUEST_H
