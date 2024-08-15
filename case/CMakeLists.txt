cmake_minimum_required(VERSION 3.16)

set(TARGET atomiq_case)
project(${TARGET} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message (CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(${TARGET}
    scr/main.cxx
    scr/objectmanager.cxx
    include/colorobject.h
    include/objectmanager.h
)

add_subdirectory(tests)


include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
