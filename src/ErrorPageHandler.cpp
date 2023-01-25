//
// Created by Richard Spindler on 20.04.21.
//

#include "TestPageHandler.hpp"
#include "RedirectHandler.hpp"
#include "FormPageHandler.hpp"
#include "MyPageHandler.hpp"
#include "urlencode.hpp"
#include "CountryDatabase.hpp"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/EscapeHTMLStream.h>

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
#include "ErrorPageHandler.hpp"

void ErroPageHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    //Sets mime type text/html application/json etc.
    response.setContentType("text/html");
    //Sets the response status 404, 200 etc.
    response.setStatus("404");

    //opens the file stream
    std::ostream& responseStream = response.send();

    responseStream << "<html><head><head><title>My  HTTP Server in C++ </title></head>";
    responseStream << "<body><h1>PAGE NOT FOUND, SORRY!</h1><p>";
    responseStream << "";
    responseStream << "</p></body></html>";
}
