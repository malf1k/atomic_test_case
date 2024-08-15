cmake_minimum_required(VERSION 3.16)

set(TARGET atomiq_case)
project(${TARGET} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${TARGET}
    src/main.cxx
    includes/colorobject.h
    includes/objectmanager.h
    src/objectmanager.cxx
)



include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
