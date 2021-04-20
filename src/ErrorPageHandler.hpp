//
// Created by Richard Spindler on 20.04.21.
//

#ifndef GEO_TARGETED_LINK_REDIRECT_ERRORPAGEHANDLER_HPP
#define GEO_TARGETED_LINK_REDIRECT_ERRORPAGEHANDLER_HPP

#include <Poco/Net/HTTPRequestHandler.h>

class ErroPageHandler: public Poco::Net::HTTPRequestHandler
{
public:

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);;
};
#endif //GEO_TARGETED_LINK_REDIRECT_ERRORPAGEHANDLER_HPP
