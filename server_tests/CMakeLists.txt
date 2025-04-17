cmake_minimum_required(VERSION 3.10)
project(ServerTests)


set(BOOST_ROOT "C:/soft/boost/boost_1_88_0")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

file(GLOB TEST_SOURCES
    "*.cpp"
)

# Создание исполняемого файла для тестов
add_executable(server_tests
    ${TEST_SOURCES}
)

# Подключение библиотек
target_link_libraries(server_tests PRIVATE
    Boost::unit_test_framework
    server_lib
)

# Установка путей для заголовочных файлов
target_include_directories(server_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
)

# Включение тестов
enable_testing()
add_test(NAME server_tests COMMAND server_tests) 