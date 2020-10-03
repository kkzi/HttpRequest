option(QT_DIR "Qt install path, like D:/local/Qt/5.15.1/msvc2019_64")

if (${QT_DIR} STREQUAL "OFF")
    if (DEFINED ENV{QT_DIR})
        set(QT_DIR $ENV{QT_DIR})
    else ()
        set(QT_DIR D:/local/Qt/5.15.1/msvc2019_64)
    endif ()
endif ()

set(Qt5_DIR ${QT_DIR}/lib/cmake/Qt5)
message(Qt5_DIR=${Qt5_DIR})
find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED)

