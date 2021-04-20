add_executable(poco-based-webserver poco-based-webserver.cpp MyPageHandler.cpp MyPageHandler.hpp FormPageHandler.cpp
		FormPageHandler.hpp
		RedirectHandler.cpp
		RedirectHandler.hpp
		TestPageHandler.cpp
		TestPageHandler.hpp
		ErrorPageHandler.cpp
		ErrorPageHandler.hpp
		HandlerFactory.cpp
		HandlerFactory.hpp)
target_link_libraries(poco-based-webserver Poco::Net Poco::Util mongoose
	Threads::Threads country_database)
target_include_directories(poco-based-webserver PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
install(TARGETS poco-based-webserver RUNTIME DESTINATION bin)

