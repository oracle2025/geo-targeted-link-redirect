project(httpd_api_example)
cmake_minimum_required(VERSION 3.19.4)

include_directories(${PROJECT_BINARY_DIR}/include)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)

include(ExternalProject)

ExternalProject_Add(mongoose-cpp
	GIT_REPOSITORY https://github.com/Gregwar/mongoose-cpp.git
	INSTALL_DIR ${PROJECT_BINARY_DIR}
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>)
