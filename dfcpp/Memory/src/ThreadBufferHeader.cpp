/* 
    @date   : 2024/1/4
    @author : Tlx
    @brief  : 线程本地的内存堆，每个线程都会有的线程级变量
*/

#include "ThreadBufferHeader.h"

namespace D_Memory{

ThreadBufferHeader::ThreadBufferHeader(MemoryManager* MemoryManager):memoryManager_ptr(MemoryManager)
{

}

ThreadBufferHeader::~ThreadBufferHeader()
{
    
}

void* ThreadBufferHeader::alloc(int size){
    
    void * ptr = nullptr;
    int object_bin = ilog2(size);       /* 判断属于哪一个bins的, 二进制划分 */
    int object_size = 1 << object_bin;  /* 对应的大小 */
    
    if(size < SMALL_SIZE)
    {
        ptr = threadBuffer_bins(object_bin).alloc(object_size);
        if(!ptr){

            /* 本地缓存中没有内存了，向交换空间申请新块 */
            ptr = memoryManager_ptr->alloc(object_size);

        }
    } else{
        /* 大内存对象 */
    }

    if (!ptr){
        printf("error\n");
        return nullptr;
    }

    return ptr;

}

/* 释放对象，挂载到对应的freelists中去 */
void ThreadBufferHeader::free(void* ptr){
    
}

}