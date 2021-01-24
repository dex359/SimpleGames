cmake_minimum_required(VERSION 3.17)
project(2048 VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)


set(SOURCE src/main.cpp
           src/canvas.cpp)

set(HEADER src/scaling.hpp
        src/canvas.hpp)


set(QT_VERSION     5)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/rsc/2048.conf DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/rsc/icon.png DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
