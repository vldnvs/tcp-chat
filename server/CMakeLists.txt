cmake_minimum_required(VERSION 3.10)
project(TCPChatServer)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск необходимых пакетов
find_package(Boost REQUIRED COMPONENTS system thread regex)

# Добавление исходных файлов
file(GLOB SOURCES
    "src/*.cpp"
)

# Добавление заголовочных файлов
file(GLOB HEADERS
    "headers/*.h"
    "headers/*.hpp"
)

# Создание библиотеки сервера
add_library(server_lib STATIC
    ${SOURCES}
    ${HEADERS}
)

# Установка путей для заголовочных файлов
target_include_directories(server_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Подключение необходимых библиотек
target_link_libraries(server_lib PRIVATE
    Boost::system
    Boost::thread
    Boost::regex
    Threads::Threads
)

