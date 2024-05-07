cmake_minimum_required(VERSION 3.25)
project(Game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

# 设置包含目录(路径要确保正确)
include_directories(./库文件/EasyX/include)
link_directories(./库文件/EasyX/lib64)
link_libraries(libeasyx.a)

# 为你的项目添加源文件
add_executable(Game main.cpp)

# 添加需要链接的 Allegro 库
target_link_libraries(Game)