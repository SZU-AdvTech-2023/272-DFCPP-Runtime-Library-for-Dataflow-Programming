# CMakeLists.txt in Memory/demo directory

# 添加可执行文件并链接 MemoryManager 库
add_executable(test test.cpp)


# 设置库头文件路径
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/src/include)


# 链接 D_Memory 库
target_link_libraries(test D_Memory pthread)
