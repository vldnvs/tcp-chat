cmake_minimum_required(VERSION 3.10)
project(ServerTests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Homebrew paths for Boost
set(BOOST_ROOT "/opt/homebrew/opt/boost")
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

file(GLOB TEST_SOURCES
    "*.cpp"
)

# Create test executable
add_executable(server_tests
    ${TEST_SOURCES}
)

# Link libraries
target_link_libraries(server_tests PRIVATE
    Boost::unit_test_framework
    server_lib
)

# Set include directories
target_include_directories(server_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/../server/headers
)

# Enable testing
enable_testing()
add_test(NAME server_tests COMMAND server_tests) 