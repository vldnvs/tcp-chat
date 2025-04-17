cmake_minimum_required(VERSION 3.10)
project(TCPChatClient)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка пути к Qt6
set(CMAKE_PREFIX_PATH "C:/soft/qtev/qt-everywhere-src-6.9.0")

# Поиск необходимых пакетов
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Добавление исходных файлов
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
)

# Добавление заголовочных файлов
file(GLOB_RECURSE HEADERS 
    "headers/*.h"
    "headers/*.hpp"
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}
)

# Подключение Qt модулей
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Установка путей для заголовочных файлов
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Включение MOC, UIC и RCC
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# Установка выходной директории
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
) 