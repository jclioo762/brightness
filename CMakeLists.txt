cmake_minimum_required(VERSION 3.22)
set(PLUGIN_NAME "brightness")

project(${PLUGIN_NAME})

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


# 启用 qt moc 的支持
set(CMAKE_AUTOMOC ON)
# 启用 qrc 资源文件的支持
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("${QT_DEFINITIONS} -DQT_PLUGIN")

# Sources files
file(GLOB_RECURSE SRCS "*.h" "*.cpp"
        "./common/"
        "./components/"
        )

find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(DtkWidget REQUIRED)

pkg_check_modules(XCB_LIBS REQUIRED IMPORTED_TARGET xcursor)
pkg_check_modules(QGSettings REQUIRED IMPORTED_TARGET gsettings-qt)
pkg_check_modules(DdeDockInterface REQUIRED dde-dock)

add_definitions("${QT_DEFINITIONS} -DQT_PLUGIN")
add_library(${PLUGIN_NAME} SHARED ${SRCS} resource/brightness.qrc)
set_target_properties(${PLUGIN_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ./)
target_include_directories(${PLUGIN_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS})

target_include_directories(${PLUGIN_NAME} PUBLIC
        ${Qt5Widgets_INCLUDE_DIRS}
        ${DtkWidget_INCLUDE_DIRS}
        ${DdeDockInterface_INCLUDE_DIRS}
        )

target_link_libraries(${PLUGIN_NAME} PRIVATE
 ${DtkWidget_LIBRARIES}
 Qt5::Widgets
 Qt5::DBus
 ${DdeDockInterface_INCLUDE_DIRS}
 Qt5::Svg)

install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION lib/dde-dock/plugins)
