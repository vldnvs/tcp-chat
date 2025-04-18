cmake_minimum_required(VERSION 3.14)

project(tcp-chat-client)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Используем Homebrew пути для Qt на macOS
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@6")

# Поиск необходимых пакетов
find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)

# Добавляем исходные файлы
set(SOURCES
    src/main.cpp
    src/chatWindow.cpp
    src/networkManager.cpp
    src/windowManager.cpp
    src/serverAddressWindow.cpp
    src/usernameWindow.cpp
    src/logger.cpp
)

# Добавляем заголовочные файлы
set(HEADERS
    headers/chatWindow.h
    headers/networkManager.h
    headers/windowManager.h
    headers/serverAddressWindow.h
    headers/usernameWindow.h
    headers/logger.h
)

# Создаем исполняемый файл
add_executable(tcp-chat-client ${SOURCES} ${HEADERS})

# Подключаем директорию с заголовочными файлами
target_include_directories(tcp-chat-client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Подключаем библиотеки Qt
target_link_libraries(tcp-chat-client PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
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