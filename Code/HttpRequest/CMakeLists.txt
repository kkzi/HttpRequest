project(HttpRequest)
cmake_minimum_required(VERSION 3.17)

include(cmake/out.cmake)

add_definitions(-DHTTPREQUEST_LIB)

include_directories(Include)
aux_source_directory(. SRCS)


find_package(Qt5 COMPONENTS Network)

add_library(HttpRequest SHARED ${SRCS})
target_link_libraries(HttpRequest Qt5::Network)
