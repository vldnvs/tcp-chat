cmake_minimum_required(VERSION 3.10)
project(chat_tests)

# Находим необходимые пакеты
find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Добавляем исходные файлы
set(TEST_SOURCES
    chat_test.cpp
)

# Создаем исполняемый файл для тестов
add_executable(chat_tests ${TEST_SOURCES})

# Подключаем заголовочные файлы
target_include_directories(chat_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${GTEST_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

# Подключаем библиотеки
target_link_libraries(chat_tests
    ${GTEST_LIBRARIES}
    ${Boost_LIBRARIES}
    pthread
)

# Добавляем тесты
include(GoogleTest)
gtest_discover_tests(chat_tests) 