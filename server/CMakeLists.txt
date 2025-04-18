cmake_minimum_required(VERSION 3.14)
project(TCPChatServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Use Homebrew paths for Boost
set(BOOST_ROOT "/opt/homebrew/opt/boost")
find_package(Boost REQUIRED COMPONENTS system thread regex)

# Add source files
file(GLOB SOURCES
    "src/*.cpp"
)

# Add header files
file(GLOB HEADERS
    "headers/*.h"
    "headers/*.hpp"
)

# Create server library
add_library(server_lib STATIC
    ${SOURCES}
    ${HEADERS}
)

# Set include directories
target_include_directories(server_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link required libraries
target_link_libraries(server_lib
    PUBLIC
        Boost::system
        Boost::thread
        Boost::regex
        Threads::Threads
)

# Create executable target
add_executable(${PROJECT_NAME} src/main.cpp)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link against server library
target_link_libraries(${PROJECT_NAME} PRIVATE server_lib)

# Platform-specific settings
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Install targets
install(TARGETS server_lib ${PROJECT_NAME}
    EXPORT server-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION Applications
    INCLUDES DESTINATION include
)

# Install headers
install(DIRECTORY headers/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# Export targets
install(EXPORT server-targets
    FILE server-targets.cmake
    NAMESPACE server::
    DESTINATION lib/cmake/server
)

