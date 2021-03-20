
add_executable(server main.cpp)
target_link_libraries(server mongoose Threads::Threads)
install(TARGETS server RUNTIME DESTINATION bin)
