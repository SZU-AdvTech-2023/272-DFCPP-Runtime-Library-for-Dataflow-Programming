/*
    @date   : 2023-12-12
    @author : Tlx
    @brief  : 线程本地的缓存队列
*/

#ifndef DFCPP_THREADBUFFER_H
#define DFCPP_THREADBUFFER_H

#include "config.h"
#include "Superblock.h"

/* 调试添加 */

#include <iostream>

/* 调试添加 */

namespace D_Memory{

/* 
    前向说明
*/

class Superblock;

/*  前向说明 */
class ThreadBuffer{
public:
    ThreadBuffer();
    ~ThreadBuffer();

    void * alloc(int size);     /* 从缓存区分配内存块 */
    void free(void * ptr);      /* 释放内存块 */

    /* 空闲缓存队列链表 */
    class FreeThreadBuffer {
        public:
        inline FreeThreadBuffer()
            : next (nullptr)
            {}
        public:
        FreeThreadBuffer * next;
        };

private:
    FreeThreadBuffer freelist;     /* 空闲内存块链表 */
    Superblock *superblock_ptr;    /* 对应的超级块指针 */

    
    /* 这里要有大小对应的bin对应的超级块链表指针 */
    /* 分组的事情交给上一级， 那交换空间的指针，不如也交给上一层，超级块的话本地就能申请了 */
    /* 这里要确定的事情只有一个，那就是大小之间统一超级块大小还是由阶数来确定对应的超级块大小 */
    /* 
        Superblock * superblock_list; 超级块链表指针 (超级块中有freelist 和 next指针)
    */

    /* 这里要有交换空间的指针 */
    /* MemoryManager * MemoryManger_ptr*/

};


}
#endif