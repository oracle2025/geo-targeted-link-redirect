//
// Created by Richard Spindler on 19.04.21.
//

#include "MyPageHandler.hpp"
#include "urlencode.hpp"
#include "CountryDatabase.hpp"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <mongoose/Utils.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/URI.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/ServerApplication.h>
#include <regex>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "FormPageHandler.hpp"

void FormPageHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    ostream& responseStream = response.send();
    ifstream fin("../src/form.html", ios_base::in | ios_base::binary);
    ostringstream oss;
    oss << fin.rdbuf();
    string content(oss.str());
    content = regex_replace( content, regex("@LINK1_URL@"), Mongoose::Utils::htmlEntities(request.get("link1", "") ));
    content = regex_replace( content, regex("@LINK2_URL@"), Mongoose::Utils::htmlEntities(request.get("link2", "") ));
    auto link = string("http://localhost:8080/redirect?")
                + url_encode(request.get("country1", ""))
                + "=" + url_encode(request.get("link1", ""))
                + "&" + url_encode(request.get("country2", ""))
                + "=" + url_encode(request.get("link2", ""));
    content = regex_replace( content, regex("@LINK_FOR_COPY_AND_PASTE@"), link );
    //@LINK_FOR_COPY_AND_PASTE@
    responseStream << content;
    responseStream << "<pre>";
    for(auto i = request.begin() ; i != request.end() ; i++ ) {
        auto header = *i;
        auto name = header.first;
        auto value = header.second;
        responseStream << Mongoose::Utils::htmlEntities(name) << ": " << Mongoose::Utils::htmlEntities(value) << "\n";
    }
    responseStream << "Method: " << request.getMethod() << "\n";
    Poco::Net::HTMLForm formdata(request, request.stream());
    for(auto i = formdata.begin() ; i != formdata.end() ; i++ ) {
        auto header = *i;
        auto name = header.first;
        auto value = header.second;
        responseStream << Mongoose::Utils::htmlEntities(name) << ": " << Mongoose::Utils::htmlEntities(value) << "\n";
    }
}
