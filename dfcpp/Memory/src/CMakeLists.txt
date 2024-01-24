# CMakeLists.txt in Memory/src directory

# 设置头文件目录
include_directories(include)
include_directories(util)

# Find the NUMA library
#find_package(NUMA REQUIRED)

file(GLOB_RECURSE source_cpp *.cpp)
# 添加源文件
add_library(D_Memory ${source_cpp})

# 链接 NUMA 库
target_link_libraries(D_Memory numa dl)
