project(httpd_api_example)
cmake_minimum_required(VERSION 3.13)

find_package(Threads)

include_directories(${PROJECT_BINARY_DIR}/include)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)

include(ExternalProject)

ExternalProject_Add(mongoose-cpp
	GIT_REPOSITORY https://github.com/Gregwar/mongoose-cpp.git
	INSTALL_DIR ${PROJECT_BINARY_DIR}
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>)

ExternalProject_Add(libmaxminddb
        URL https://github.com/maxmind/libmaxminddb/releases/download/1.5.2/libmaxminddb-1.5.2.tar.gz
        URL_HASH MD5=cf6b3d84f7e0379b2ff9ad09f7c3184f
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
        DOWNLOAD_NO_PROGRESS ON
        CMAKE_ARGS
                -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
        )
