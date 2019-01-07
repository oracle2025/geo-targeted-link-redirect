#include <boost/process.hpp> 
#include <boost/assign/list_of.hpp> 
#include <string> 
#include <vector> 

using namespace boost::process; 

int main() 
{ 
  std::string exec = find_executable_in_path("notepad.exe"); 
  std::vector<std::string> args = boost::assign::list_of("notepad.exe"); 
  context ctx; 
  ctx.environment = self::get_environment(); 
  launch(exec, args, ctx); 
} 
