cmake_minimum_required(VERSION 3.22)
project(Client)

# Set the minimum required Qt version
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find in Linux file system
# Use an external command to find the path to the directory (d), starting from /home.
# Write the result in QT_DIR.
# Last argument - strip the string of extra characters and spaces
execute_process(COMMAND find /home -type d -path "*Qt/5.15.2/gcc_64/lib/cmake"
    OUTPUT_VARIABLE QT_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if (QT_DIR)
    list(APPEND CMAKE_PREFIX_PATH "${QT_DIR}")
    message(STATUS "Set CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
else()
    message(FATAL_ERROR "Could not find Qt directory")
endif()


find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

include_directories(
    /usr/include # for lgmp
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_CURRENT_SOURCE_DIR}/styles
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientback.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/encryption.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/registration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# moc files will not work unless the headers are assembled
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/client.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/clientback.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/encryption.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/registration.hpp
)

set(FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/forms/client.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/forms/registration.ui
)

set(QRC ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)

# Generate executable
add_executable(Client ${SOURCES} ${HEADERS} ${FORMS} ${QRC})

# Link libraries
target_link_libraries(Client PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    -lgmp
)

# To specify where the .ui files are located
set_target_properties(Client PROPERTIES AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

