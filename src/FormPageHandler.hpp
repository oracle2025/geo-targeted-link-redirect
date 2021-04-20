//
// Created by Richard Spindler on 19.04.21.
//

#ifndef GEO_TARGETED_LINK_REDIRECT_FORMPAGEHANDLER_HPP
#define GEO_TARGETED_LINK_REDIRECT_FORMPAGEHANDLER_HPP
#include <Poco/Net/HTTPServer.h>

class FormPageHandler: public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

};
#endif //GEO_TARGETED_LINK_REDIRECT_FORMPAGEHANDLER_HPP
