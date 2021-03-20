configure_file(config.h.in config.h @ONLY)
add_executable(server main.cpp config.h)
target_link_libraries(server mongoose Threads::Threads maxminddb)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(server
	PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS off
	)
install(TARGETS server RUNTIME DESTINATION bin)
