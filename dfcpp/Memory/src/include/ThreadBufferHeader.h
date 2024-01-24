/*
    @date   : 2023-12-12
    @author : Tlx
    @brief  : 缓存队列管理器
*/

#ifndef DFCPP_BUFFERMANAGER_HPP
#define DFCPP_BUFFERMANAGER_HPP

/*
    线程本地的缓存队列，会绑定对应的线程堆，每种size具有一个缓存队列
    有缓存队列的内存数据大小范围
*/


#include "array.h"
#include "config.h"
#include "ThreadBuffer.h"
#include "calculate.h"
#include "MemoryManager.h"

namespace D_Memory{
    class ThreadBuffer;
    class MemoryManager;
/* 
    线程的本地堆，每一个线程都有一个这样子的线程对象 
    这是线程本地内存与交换空间的接口
*/
class ThreadBufferHeader{
public:
    ThreadBufferHeader(MemoryManager*);
    ~ThreadBufferHeader();

    void* alloc(int size); // 申请对应大小的空间
    void free(void* ptr); // 释放对应的指针

private:
    Array<BINS, ThreadBuffer> threadBuffer_bins; /* 每种不同的size对应的ThreadBuffer */
    MemoryManager * memoryManager_ptr;           /* 内存管理器指针 */
};

}
#endif