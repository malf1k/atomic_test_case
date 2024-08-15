cmake_minimum_required(VERSION 3.16)

set(TARGET atomiq_tests)
project(${TARGET} LANGUAGES CXX)
enable_testing()

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(${TARGET} tests.cxx)
target_link_libraries(${TARGET} PRIVATE Catch2::Catch2WithMain)

