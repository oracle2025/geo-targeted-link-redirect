#include <iostream>
#include <thread>
#include <chrono>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>

using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
    public: 
        void hello(Request &request, StreamResponse &response)
        {
            response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
        }

        void setup()
        {
            addRoute("GET", "/hello", MyController, hello);
        }
};

int main(int argc, const char *argv[])
{
 	MyController myController;
    Server server(8080);
    server.registerController(&myController);

    server.start(); 

    while (1) {
		this_thread::sleep_for(chrono::milliseconds(10));
    }

	return 0;
}
