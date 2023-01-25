project(geo-targeted-link-redirect)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib/cmake)

find_package(Threads)
find_package(Poco COMPONENTS Net Util)

include_directories(${PROJECT_BINARY_DIR}/include)
link_directories(${PROJECT_BINARY_DIR}/lib)

set(GEOLITE2_COUNTRY_DATABASE_FILENAME "${PROJECT_SOURCE_DIR}/share/GeoLite2-Country.mmdb" CACHE FILEPATH "Filepath for GeoLite2-Country.mmdb https://dev.maxmind.com/geoip/geoip2/geolite2/")

add_subdirectory(src)
add_subdirectory(test)

include(ExternalProject)

ExternalProject_Add(libmaxminddb
        URL https://github.com/maxmind/libmaxminddb/releases/download/1.5.2/libmaxminddb-1.5.2.tar.gz
        URL_HASH MD5=cf6b3d84f7e0379b2ff9ad09f7c3184f
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
        DOWNLOAD_NO_PROGRESS ON
        CMAKE_ARGS
                -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
        )

if(NOT ${Poco_FOUND})
	ExternalProject_Add(libpoco
		GIT_REPOSITORY https://github.com/pocoproject/poco.git
		GIT_TAG poco-1.10.1-release
		GIT_SHALLOW ON
		GIT_PROGRESS OFF
		INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
		CMAKE_ARGS
			-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
		)
endif()

