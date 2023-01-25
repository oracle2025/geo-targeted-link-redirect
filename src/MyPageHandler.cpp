//
// Created by Richard Spindler on 19.04.21.
//

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
#include "MyPageHandler.hpp"

void MyPageHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream& responseStream = response.send();

    responseStream << "<html><head><head><title>My  HTTP Server in C++ </title></head>";
    responseStream << "<body><h1>Hello World</h1><p>";
    responseStream << "";
    responseStream << "</p></body></html>";
}
