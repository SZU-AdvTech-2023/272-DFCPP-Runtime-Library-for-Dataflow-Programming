# CMakeLists.txt in Memory directory
cmake_minimum_required(VERSION 3.0)
# 设置项目名称
project(D_Memory)

# 设置 C++ 版本
set(CMAKE_CXX_STANDARD 11)

# 如果用户没有指定构建类型，则默认为 Debug 模式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type: Debug" FORCE)
endif()

# 检查是否为 Release 模式
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release mode enabled")
    # 添加 Release 模式下的宏定义或其他设置
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")  # 设置 Release 编译选项
endif()

# 添加 Memory 子目录
add_subdirectory(src)
add_subdirectory(demo)
