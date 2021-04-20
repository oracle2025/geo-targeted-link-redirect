//
// Created by Richard Spindler on 19.04.21.
//

#ifndef GEO_TARGETED_LINK_REDIRECT_REDIRECTHANDLER_HPP
#define GEO_TARGETED_LINK_REDIRECT_REDIRECTHANDLER_HPP

#include <Poco/Net/HTTPRequestHandler.h>
#include "CountryDatabase.hpp"

class RedirectHandler: public Poco::Net::HTTPRequestHandler {
    CountryDatabase countries;
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};
#endif //GEO_TARGETED_LINK_REDIRECT_REDIRECTHANDLER_HPP
