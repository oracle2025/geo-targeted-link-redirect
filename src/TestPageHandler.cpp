//
// Created by Richard Spindler on 19.04.21.
//

#include "RedirectHandler.hpp"
#include "FormPageHandler.hpp"
#include "MyPageHandler.hpp"
#include "urlencode.hpp"
#include "CountryDatabase.hpp"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/EscapeHTMLStream.h>
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
#include "TestPageHandler.hpp"

void TestPageHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream& responseStream = response.send();

    responseStream << "<html><head><head><title>My  HTTP Server in C++ </title></head>";
    responseStream << "<body><h1>Hello World 2</h1><p>";
    responseStream << "";
    responseStream << "</p>";
    responseStream << "<pre>";

    for(auto i = request.begin() ; i != request.end() ; i++ ) {
        auto header = *i;
        auto name = header.first;
        auto value = header.second;
        Poco::Net::EscapeHTMLOutputStream out(responseStream);
        out << (name) << ": " << (value) << "\n";
    }

    if (request.has("x-forwarded-for")) {
        auto remote_ip_addr = request.get("x-forwarded-for");
        auto iso_code = countries.lookupIsoCode(remote_ip_addr);
        responseStream << "Iso-Code: " << iso_code << "\n";
    }

    responseStream << "</pre>";
    responseStream << "</body></html>";
}
