project(TestHttpRequest)

message(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Code/HttpRequest/Include)
aux_source_directory(. SRCS)

find_package(Qt5 COMPONENTS NetWork)
add_executable(TestHttpRequest ${SRCS})
target_link_libraries(TestHttpRequest HttpRequest)