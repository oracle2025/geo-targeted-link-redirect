//
// Created by Richard Spindler on 20.04.21.
//

#include "ErrorPageHandler.hpp"
#include "TestPageHandler.hpp"
#include "RedirectHandler.hpp"
#include "FormPageHandler.hpp"
#include "MyPageHandler.hpp"
#include "urlencode.hpp"
#include "CountryDatabase.hpp"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/URI.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/ServerApplication.h>
#include <regex>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "HandlerFactory.hpp"

Poco::Net::HTTPRequestHandler *HandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
    // choose response based uri
    if(request.getURI()=="/"){
        return new MyPageHandler();
    }
    if(request.getURI()=="/test"){
        return new TestPageHandler();
    }
    if(request.getURI()=="/form"){
        return new FormPageHandler();
    }
    if(request.getURI()=="/redirect"){
        return new RedirectHandler();
    }
    //uri not recognized
    return new ErroPageHandler();
}
