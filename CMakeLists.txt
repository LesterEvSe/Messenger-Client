cmake_minimum_required(VERSION 3.22)
project(Client)

# Set the minimum required Qt version
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/home/zhenia/Qt/5.15.2/gcc_64/lib/cmake")

find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

# Add include directories
include_directories(
    /usr/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_CURRENT_SOURCE_DIR}/styles
)

# Add source files
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

# Add UI files
set(FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/forms/client.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/forms/registration.ui
)


# Add res files
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

set_target_properties(Client PROPERTIES AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

