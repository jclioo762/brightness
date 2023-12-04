cmake_minimum_required(VERSION 3.22)

set(PLUGIN_NAME "brightness")

project(${PLUGIN_NAME})

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Header files
file(GLOB_RECURSE SRCS
    "*.h"
    "./common/*.h"
    "./components/*.h"
    )

# Source files
file(GLOB_RECURSE HDRS
    "*.cpp"
    "./common/*.cpp"
    "./components/*.cpp"
    )

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(DtkWidget REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(XCB_LIBS REQUIRED IMPORTED_TARGET xcursor)
pkg_check_modules(QGSettings REQUIRED IMPORTED_TARGET gsettings-qt)
pkg_check_modules(DdeDockInterface REQUIRED dde-dock)

add_definitions("${QT_DEFINITIONS} -DQT_PLUGIN")
add_library(${PLUGIN_NAME} SHARED ${SRCS} ${HDRS} resource/brightness.qrc)
set_target_properties(${PLUGIN_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PLUGIN_NAME} PUBLIC
        ${Qt5Widgets_INCLUDE_DIRS}
        ${DtkWidget_INCLUDE_DIRS}
        ${DdeDockInterface_INCLUDE_DIRS}
        )

target_link_libraries(${PLUGIN_NAME} PRIVATE
    Qt5::DBus
    Qt5::Svg
    Qt5::Widgets
    ${DtkWidget_LIBRARIES}
    ${DdeDockInterface_INCLUDE_DIRS}
    )

set(CMAKE_INSTALL_PREFIX "/usr")

install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/dde-dock/plugins)
