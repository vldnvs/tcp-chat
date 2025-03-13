cmake_minimum_required (VERSION 2.6)
project (Chat)
cmake_minimum_required(VERSION 3.10)
project(ChatApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(Headers)

set(SOURCES
    src/main.cpp
    src/user.cpp
    src/server.cpp
    src/room.cpp
)

set(HEADERS
    headers/user.h
    headers/server.h
    headers/room.h
)


find_package(Boost REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Boost::system Boost::thread Boost::regex)
