/*
    @date   :  2023-12-12
    @author :  Tlx
    @brief  :  暴露出来的内存分配接口
*/

#ifndef DFCPP_MEMORYALLOCATOR_H
#define DFCPP_MEMORYALLOCATOR_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <numa.h>
#include "MemoryManager.h"
/* ---------------------------------------------------------------全局变量区域 */

/* 获取全局管理器 */
using D_Memory::MemoryManager;
MemoryManager* myMemoryManager = MemoryManager::get_instance();


/* ---------------------------------------------------------------全局变量区域 */


/* ---------------------------------------------------------------malloc重载 */
extern void* _xxmalloc(size_t size);
extern void _xxfree(void* ptr);
// 重载 malloc 和 free
extern "C" {
    #define malloc(size) _xxmalloc(size);
    #define free(ptr) _xxfree(ptr);
}
// 重载 new 和 delete
void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
/* ---------------------------------------------------------------malloc重载 */

int i = 4;


#endif