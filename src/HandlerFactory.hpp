//
// Created by Richard Spindler on 20.04.21.
//

#ifndef GEO_TARGETED_LINK_REDIRECT_HANDLERFACTORY_HPP
#define GEO_TARGETED_LINK_REDIRECT_HANDLERFACTORY_HPP

#include <Poco/Net/HTTPRequestHandlerFactory.h>

//  Url Router
class HandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest &request);
};
#endif //GEO_TARGETED_LINK_REDIRECT_HANDLERFACTORY_HPP
