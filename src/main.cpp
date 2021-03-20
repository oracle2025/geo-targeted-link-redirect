#include <iostream>
#include <thread>
#include <chrono>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include <maxminddb.h>
#include <cstring>
#include "config.h"

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    public: 
        void hello(Request &request, StreamResponse &response)
        {
            response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
        }

	void ip(Request &request, StreamResponse &response)
	{
		auto vars = request.getAllHeaders();

		auto forwarded_ip = "X-FORWARDED-FOR";

		response << "Size: " << vars.size() << "<br>\n";
		response << "Remote Address: " << request.getRemoteAddr() << "<br>\n";
		for (auto i : vars) {
			response << htmlEntities(i.first) << ": " << htmlEntities(i.second) << "<br>\n";
		}
	}

	void redirect(Request &request, StreamResponse &response)
	{
		response.setHeader("Location", "https://bunfet.me/");
		response.setCode(301);
	}

        void setup()
        {
            addRoute("GET", "/hello", MyController, hello);
            addRoute("GET", "/ip", MyController, ip);
            addRoute("GET", "/redirect", MyController, redirect);
        }
};

int main(int argc, const char *argv[])
{
  MMDB_s mmdb;
      int status = MMDB_open(GEOLITE2_COUNTRY_DATABASE_FILENAME, MMDB_MODE_MMAP, &mmdb);

	if (MMDB_SUCCESS != status) {
		std::cerr << "Can't open " << GEOLITE2_COUNTRY_DATABASE_FILENAME << " - " << MMDB_strerror(status) << "\n";

		if (MMDB_IO_ERROR == status) {
			std::cerr << "    IO error: " << std::strerror(errno) << "\n";
		}
		return EXIT_FAILURE;
	  }


 	MyController myController;
    Server server(8080);
    server.registerController(&myController);

    std::cout << "Starting Server\n";

    server.start(); 

    while (1) {
		this_thread::sleep_for(chrono::milliseconds(10));
    }

	return 0;
}
