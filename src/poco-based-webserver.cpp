#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/URI.h>

#include <Poco/Net/HTTPRequestHandlerFactory.h>


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "CountryDatabase.hpp"
#include "urlencode.hpp"
#include "MyPageHandler.hpp"
#include "FormPageHandler.hpp"
#include "RedirectHandler.hpp"
#include "TestPageHandler.hpp"
#include "ErrorPageHandler.hpp"
#include "HandlerFactory.hpp"

using namespace std;

// Page renderer for /Test uri


// Server  Application
class MyWebHTTPServerApplication : public Poco::Util::ServerApplication
{
protected:
	int main(const std::vector<std::string> &args){

         //Port to listen
		Poco::UInt16 port = std::atoi(std::getenv("PORT"));

			Poco::Net::ServerSocket socket(port);

			Poco::Net::HTTPServerParams *pParams = new Poco::Net::HTTPServerParams();
			//Sets the maximum number of queued connections.
			pParams->setMaxQueued(100);
			//Sets the maximum number of simultaneous threads available for this Server
			pParams->setMaxThreads(16);
            // Instanciate HandlerFactory
			Poco::Net::HTTPServer server(new HandlerFactory(), socket, pParams);

			server.start();

			waitForTerminationRequest();

			server.stop();

			return EXIT_OK;

	}
};



// Macros to setup maim function to run as app or deamon (service in windows)
POCO_SERVER_MAIN(MyWebHTTPServerApplication);
