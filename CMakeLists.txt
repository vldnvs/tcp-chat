cmake_minimum_required(VERSION 3.10)
project(TCPChat VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(Threads REQUIRED)

# Set Boost paths for macOS
set(BOOST_ROOT "/opt/homebrew/opt/boost")
find_package(Boost REQUIRED COMPONENTS system thread regex unit_test_framework)

# Set Qt paths for macOS
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@6")
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Verify Boost installation
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Global include directories
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Build options
# option(BUILD_TESTS "Build the tests" ON)
# option(BUILD_SERVER_TESTS "Build the server tests" OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add subdirectories for components
add_subdirectory(server)
add_subdirectory(client)

# Configure tests if enabled
# if(BUILD_TESTS)
#     enable_testing()
#     # Добавляем серверные тесты только если включена соответствующая опция
#     if(BUILD_SERVER_TESTS)
#         add_subdirectory(server_tests)
#     endif()
# endif()

# Print build information
message(STATUS "Building components:")
message(STATUS "  - Server executable: chat_server")
message(STATUS "  - Client executable: chat_client")
# if(BUILD_TESTS AND BUILD_SERVER_TESTS)
#     message(STATUS "  - Server tests: server_tests")
# endif()
