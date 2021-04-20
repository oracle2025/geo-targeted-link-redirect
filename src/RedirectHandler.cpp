//
// Created by Richard Spindler on 19.04.21.
//

#include "RedirectHandler.hpp"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>


bool validateUrl(std::string u){
    try {
        Poco::URI uri(u);
    }
    catch (Poco::SyntaxException &e){
        return false;
    }
    return true;
}

void RedirectHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    std::string remote_ip_addr;
    if (request.has("x-forwarded-for")) {
        remote_ip_addr = request.get("x-forwarded-for");
    }
    auto iso_code = countries.lookupIsoCode(remote_ip_addr);
    std::string uri;
    if (request.has(iso_code)) {
        uri = request.get(iso_code);
    }
    if (validateUrl(uri)) {
        response.set("Location", uri);
        response.setStatus("301");
    }
}
