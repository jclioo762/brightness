cmake_minimum_required(VERSION 3.22)

project(dde-dock-brightness-plugin)

if (NOT DEFINED VERSION)
    set(VERSION 1.0.0)
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# 启用 qt moc 的支持
set(CMAKE_AUTOMOC ON)
# 启用 qrc 资源文件的支持
set(CMAKE_AUTORCC ON)
# 启用 ui 文件的支持
#set(CMAKE_AUTOUIC ON)

# generate a compile commands file as complete database for vim-YouCompleteMe or some other similar tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(src)
