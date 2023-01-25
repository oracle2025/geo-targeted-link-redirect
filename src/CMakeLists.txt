configure_file(config.h.in config.h @ONLY)

add_library(country_database config.h CountryDatabase.cpp CountryDatabase.hpp
	urlencode.cpp urlencode.hpp)
target_link_libraries(country_database maxminddb)
target_include_directories(country_database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_library(server config.h CountryDatabase.cpp CountryDatabase.hpp
	urlencode.cpp urlencode.hpp ShutdownEvent.cpp ShutdownEvent.hpp)
target_link_libraries(server mongoose Threads::Threads maxminddb)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(server
	PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS off
	)
if(APPLE)
	# for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
endif()
if(UNIX AND NOT APPLE)
	# for Linux, BSD, Solaris, Minix
endif()

# Try this: https://rg42.org/wiki/embedding_resources_in_executables
# string( MAKE_C_IDENTIFIER "form.html" input_identifier )
# set( output "${CMAKE_CURRENT_BINARY_DIR}/${input_identifier}.o" )
# add_custom_command(
#		OUTPUT ${output}
#		COMMAND ${CMAKE_LINKER} --relocatable --format binary --output ${output} "form.html"
#		#COMMAND gcc -sectcreate __DATA __example_jpg example.jpg -o myapp myapp.c
#		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#		DEPENDS form.html
#)
#add_custom_target( rc ALL DEPENDS ${output} )

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
	target_link_libraries(poco-based-webserver Poco::Net Poco::Util
		Threads::Threads country_database ${output})
	target_include_directories(poco-based-webserver PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
	install(TARGETS poco-based-webserver RUNTIME DESTINATION bin)
	set_target_properties(poco-based-webserver
			PROPERTIES
			CXX_STANDARD 14
			CXX_EXTENSIONS off
			)
endif()
