configure_file(config.h.in config.h @ONLY)

add_library(country_database config.h CountryDatabase.cpp CountryDatabase.hpp
	urlencode.cpp urlencode.hpp)
target_link_libraries(country_database maxminddb)
target_include_directories(country_database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable(server main.cpp config.h CountryDatabase.cpp CountryDatabase.hpp
	urlencode.cpp urlencode.hpp ShutdownEvent.cpp ShutdownEvent.hpp)
target_link_libraries(server mongoose Threads::Threads maxminddb)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(server
	PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS off
	)
install(TARGETS server RUNTIME DESTINATION bin)
if(${Poco_FOUND})
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
endif()
