cmake_minimum_required(VERSION 3.16)

set(TARGET atomiq_case)
project(${TARGET} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(${TARGET}
    scr/main.cxx
    scr/objectmanager.cxx
    include/colorobject.h
    include/objectmanager.h
)

option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    message(STATUS "ENABLE_TESTS = ${ENABLE_TESTS}" )
    enable_testing()

    Include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.7.0 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)

    add_executable("${TARGET}_test" tests/tests.cxx scr/objectmanager.cxx)
    target_link_libraries("${TARGET}_test" PRIVATE Catch2::Catch2WithMain)


    include(GNUInstallDirs)
    install(TARGETS ${TARGET}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
