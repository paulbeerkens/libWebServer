cmake_minimum_required(VERSION 3.8)

set(SOURCE_FILES
        UrlRequest.cpp
        UrlRequest.h
        WebServer.cpp
        WebServer.h)

add_library(libWebServer ${SOURCE_FILES})

add_definitions (-DLIBWEBSERVERVERSION="${PROJECT_VERSION}")

message (STATUS ${CMAKE_CURRENT_SOURCE_DIR})
message (STATUS ${CMAKE_INSTALL_PREFIX})

#allows this library to be included with #include <DIRNAME/FILENAME>
target_include_directories (libWebServer INTERFACE ../.)

#target_include_directories (libWebServer INTERFACE ../.
#        $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}>
#        $<INSTALL_INTERFACE: ${CMAKE_INSTALL_PREFIX}>
#        )