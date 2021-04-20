//
// Created by Richard Spindler on 19.04.21.
//

#ifndef GEO_TARGETED_LINK_REDIRECT_MYPAGEHANDLER_HPP
#define GEO_TARGETED_LINK_REDIRECT_MYPAGEHANDLER_HPP
// Page renderer for / uri
#include <Poco/Net/HTTPRequestHandler.h>

class MyPageHandler: public Poco::Net::HTTPRequestHandler
{
public:

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};
#endif //GEO_TARGETED_LINK_REDIRECT_MYPAGEHANDLER_HPP
