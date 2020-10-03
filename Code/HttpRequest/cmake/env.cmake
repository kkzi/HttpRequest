if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH 64)
else ()
    set(ARCH 32)
endif ()

if (${ARCH} STREQUAL "32")
    message(FATAL_ERROR "NOT support 32 bit yet")
endif ()

set(PLATFORM ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})
message(${CMAKE_CXX_COMPILER})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)