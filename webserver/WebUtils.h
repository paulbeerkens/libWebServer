#ifndef LIBWEBSERVER_WEBUTILS_H
#define LIBWEBSERVER_WEBUTILS_H

#include <vector>
#include <sstream>

namespace webserver {

//Length function to be used on constexpr
//the (&) is basically an anonomous variable. Could have been [maybe_unused] char const (&array) [N])
//Remember arrays can only be passed by reference hence the (&).
template <std::size_t N>
constexpr std::size_t length (char const (&) [N])
{
    return N-1;
}

inline std::vector<std::string> split (const std::string& s, char delim) {
    std::stringstream ss (s);
    std::string token;
    std::vector <std::string> retVal;
    while (std::getline (ss, token, delim)) {
        if (!token.empty()) {//we are skipping empty values (double delimiter)
            retVal.push_back(token);
        }
    }
    return retVal;
}

}

#endif //LIBWEBSERVER_WEBUTILS_H
