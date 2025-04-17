cmake_minimum_required(VERSION 3.10)
project(TCPChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/headers)

set(SOURCES
    src/main.cpp
    src/user.cpp
    src/server.cpp
    src/room.cpp
    src/logger/logger.cpp
)

set(HEADERS
    headers/user.h
    headers/server.h
    headers/room.h
)

find_package(Boost REQUIRED COMPONENTS system thread regex unit_test_framework)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Boost::system Boost::thread Boost::regex)

option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
    enable_testing()
    
    if(EXISTS ${CMAKE_SOURCE_DIR}/tests/chat_tests.cpp)
        set(TEST_SOURCES
            tests/chat_tests.cpp
            src/user.cpp
            src/server.cpp
            src/room.cpp
            src/logger/logger.cpp
        )
        
        add_executable(chat_tests ${TEST_SOURCES} ${HEADERS})
        target_link_libraries(chat_tests Boost::system Boost::thread Boost::regex Boost::unit_test_framework)
        add_test(NAME ChatTests COMMAND chat_tests)
    else()
        message(WARNING "Test file tests/chat_tests.cpp not found. Tests will not be built.")
    endif()
endif()

add_subdirectory(server)
add_subdirectory(client)
