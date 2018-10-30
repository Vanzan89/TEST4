cmake_minimum_required(VERSION 2.8.12)

project(project-src LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Network REQUIRED)
aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)
file(GLOB MOC_HDRS ${PROJECT_SOURCE_DIR}/*hpp)
add_executable(${PROJECT_NAME} "main.cpp" ${SRCS} ${MOC_HDRS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)
