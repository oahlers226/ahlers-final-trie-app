cmake_minimum_required(VERSION 3.10)
project(trie-app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(code)
include_directories(app)
include_directories(tests)

file(GLOB SOURCES "code/*.cpp")
file(GLOB APP_SOURCES "app/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(trie-app ${APP_SOURCES} ${SOURCES})
add_executable(trie-tests ${TEST_SOURCES} ${SOURCES})

enable_testing()
add_test(NAME TrieUnitTests COMMAND trie-tests)