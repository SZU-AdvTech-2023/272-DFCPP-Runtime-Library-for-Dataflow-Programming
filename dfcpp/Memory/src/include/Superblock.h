/*
    @date   :  2023-12-12
    @author :  Tlx
    @brief  :  线程管理的超级块，每个超级块管理一种固定类型大小的内存分配工作
*/

#ifndef DFCPP_SUPERBLOCK_H
#define DFCPP_SUPERBLOCK_H

#include "ThreadBuffer.h"
/* 调试添加 */
#include <numa.h>
#include <iostream>
/* 调试添加 */

namespace D_Memory{

/* 
    超级块的结构 32768
    @freelist : 空闲内存块链表
    @current_ptr : 当前的空闲块地址
    @object_size : 当前对象块大小
*/
/* 前向说明 */
class ThreadBuffer;
/* 前向说明 */

class Superblock{

public:
    Superblock(int size);
    ~Superblock();

    void* alloc(int size);     /* 从超级块分配内存块 */
    void free(void * ptr);      /* 释放内存块 */

private:
    /* 这里要有交换空间的指针 */
    ThreadBuffer* threadBuffer_ptr;  /* 空闲内存块链表 */
    void* current_ptr;      /* 当前的空闲块地址 */
    int object_size;        /* 当前对象块大小 */
};



}
#endif