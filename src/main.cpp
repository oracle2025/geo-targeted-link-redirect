#include <iostream>
#include <thread>
#include <chrono>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include "CountryDatabase.hpp"
#include <fstream>
#include <regex>
#include "urlencode.hpp"
#include "ShutdownEvent.hpp"

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    CountryDatabase countries;
    public: 
        void index(Request &request, StreamResponse &response)
	{
	std::cout << "index() Content Type" << std::endl;
		response.setHeader("Content-Type", "text/html; charset=UTF-8");
	std::cout << "index() Connection" << std::endl;
		response.setHeader("Connection", "close");
	std::cout << "Response" << std::endl;
		response << "<!DOCTYPE html>\n"
			<< "<html>\n"
			<< "<h1>Hello world</h1>\n"
			<< "</html>";
	std::cout << "Returning" << std::endl;
	}
        void hello(Request &request, StreamResponse &response)
        {
            response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
        }

	void ip(Request &request, StreamResponse &response)
	{
		auto vars = request.getAllHeaders();

		response.setHeader("Content-Type", "text/html; charset=UTF-8");
		response.setHeader("Connection", "close");
		auto forwarded_ip = "X-FORWARDED-FOR";

		response << "Size: " << vars.size() << "<br>\n";
		response << "Remote Address: " << request.getRemoteAddr() << "<br>\n";
		for (auto i : vars) {
			response << htmlEntities(i.first) << ": " << htmlEntities(i.second) << "<br>\n";
		}
		response <<"----<br>";
		auto variables = request.getAllVariable();
        for (auto i : variables) {
            response << htmlEntities(i.first) << ": " << htmlEntities(i.second) << "<br>\n";
        }
        response << htmlEntities(request.get("DE", ""));
        response << "<br>\n";
        response << htmlEntities(request.get("EN", ""));
	}

	void redirect(Request &request, StreamResponse &response)
	{
		auto headers = request.getAllHeaders();
		std::string remote_ip_addr;

		for (auto &header: headers) {
			std::ostringstream ss;
			ss << std::uppercase << header.first;
			auto key = ss.str();
			if (key == "X-FORWARDED-FOR") {
				remote_ip_addr = header.second;
				break;
			}
		}
		auto iso_code = countries.lookupIsoCode(remote_ip_addr);
		auto uri  = request.get(iso_code, "http://localhost:8080/form");

		/* 1) get ISO_CODE for ip
		 * 2) check if parameter for iso_code
		 * 3) -> NO -> go to default parameter
		 * 4) -> Yes -> go to parameter value
		 *
		 * 5) WHAT IS the DEfault?
		 */

		/* Filter URL SAFE:
		 * There are two sets of characters you need to watch out for:
		 * reserved and unsafe.
		 *
unreserved: ALPHA  DIGIT  "-" / "." / "_" / "~"

		 The reserved characters are:

		 ampersand ("&")
		 dollar ("$")
		 plus sign ("+")
		 comma (",")
		 forward slash ("/")
		 colon (":")
		 semi-colon (";")
		 equals ("=")
		 question mark ("?")
		 'At' symbol ("@")
		 pound ("#").

		 The characters
		 generally
		 considered unsafe
		are:

		space (" ")
		less than
		and
		greater
		than
		("<>")
		open
		and
		close
		brackets
		("[]")
		open
		and
		close
		braces
		("{}")
		pipe
		("|")
		backslash
		("")
		caret
		("^")
		percent
		("%")

		*/


		response.setHeader("Location", uri);//"https://bunfet.me/");
		response.setCode(301);
	}
	void form(Request &request, StreamResponse &response)
	{
		std::ifstream fin("../src/form.html", std::ios::in | std::ios::binary);
		std::ostringstream oss;
		oss << fin.rdbuf();
		std::string content(oss.str());
		content = std::regex_replace( content, std::regex("@LINK1_URL@"), htmlEntities(request.get("link1", "") ));
		content = std::regex_replace( content, std::regex("@LINK2_URL@"), htmlEntities(request.get("link2", "") ));
		auto link = std::string("http://localhost:8080/redirect?")
		        + url_encode(request.get("country1", ""))
		        + "=" + url_encode(request.get("link1", ""))
		        + "&" + url_encode(request.get("country2", ""))
		        + "=" + url_encode(request.get("link2", ""));
        content = std::regex_replace( content, std::regex("@LINK_FOR_COPY_AND_PASTE@"), link );
        //@LINK_FOR_COPY_AND_PASTE@
		response << content;
	}

        void setup()
        {
	std::cout << "setup()" << std::endl;
            addRoute("GET", "/", MyController, index);
            addRoute("GET", "/hello", MyController, hello);
            addRoute("GET", "/ip", MyController, ip);
            addRoute("GET", "/redirect", MyController, redirect);
            addRoute("GET", "/form", MyController, form);
            addRoute("POST", "/form", MyController, form);
        }
};

int main(int argc, const char *argv[])
{
	try {
	MyController myController;
	Server server(std::atoi(std::getenv("PORT")));
	server.registerController(&myController);

	std::cout << "Starting Server" << std::endl;

	server.start(); 

	//waitShutdownEvent();
	while (1) {
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	} catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
